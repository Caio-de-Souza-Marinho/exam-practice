#!/bin/bash

PORT=8080
PASS=0
FAIL=0

pass() { echo "✓ $1"; PASS=$((PASS+1)); }
fail() { echo "✗ $1"; FAIL=$((FAIL+1)); }

# kill any leftover server
pkill mini_serv 2>/dev/null
sleep 0.2

# compile
gcc -Wall mini_serv.c -o mini_serv 2>/dev/null || { echo "COMPILATION FAILED"; exit 1; }

# ── test 1: wrong number of arguments ──
ERR=$(./mini_serv 2>&1)
[ "$ERR" = "Wrong number of arguments" ] && pass "wrong args" || fail "wrong args (got: '$ERR')"

ERR=$(./mini_serv 1 2 2>&1)
[ "$ERR" = "Wrong number of arguments" ] && pass "too many args" || fail "too many args"

# start server
./mini_serv $PORT &
SERVER_PID=$!
sleep 0.2

# ── test 2: arrival announcements ──
OUT1=$(mktemp)
OUT2=$(mktemp)

nc 127.0.0.1 $PORT > $OUT1 &
NC1_PID=$!
sleep 0.1

nc 127.0.0.1 $PORT > $OUT2 &
NC2_PID=$!
sleep 0.1

nc 127.0.0.1 $PORT > /dev/null &
NC3_PID=$!
sleep 0.1

kill $NC3_PID 2>/dev/null
sleep 0.2

grep -q "server: client .* just arrived" $OUT1 && pass "arrival seen by client 0" || fail "arrival not seen by client 0"
grep -q "server: client .* just arrived" $OUT2 && pass "arrival seen by client 1" || fail "arrival not seen by client 1"

# ── test 3: departure announcement ──
grep -q "server: client .* just left" $OUT1 && pass "departure seen by client 0" || fail "departure not seen by client 0"
grep -q "server: client .* just left" $OUT2 && pass "departure seen by client 1" || fail "departure not seen by client 1"

# ── test 4: message broadcast ──
OUT_MSG=$(mktemp)
nc 127.0.0.1 $PORT > $OUT_MSG &
NC4_PID=$!
sleep 0.1

printf "hello\n" | nc -q 1 127.0.0.1 $PORT
sleep 0.2

grep -q "client.*hello" $OUT_MSG && pass "message broadcast" || fail "message broadcast"

# ── test 5: multi-line message ──
OUT_MULTI=$(mktemp)
nc 127.0.0.1 $PORT > $OUT_MULTI &
NC5_PID=$!
sleep 0.1

printf "Hello\n\nWorld\n" | nc -q 1 127.0.0.1 $PORT
sleep 0.2

grep -q "Hello" $OUT_MULTI && pass "multiline: first line" || fail "multiline: first line"
grep -q "World" $OUT_MULTI && pass "multiline: last line" || fail "multiline: last line"
grep -q "client.*: $" $OUT_MULTI && pass "multiline: empty line prefixed" || fail "multiline: empty line not prefixed"

# ── test 6: sender doesn't receive own message ──
OUT_SELF=$(mktemp)
printf "selftest\n" | nc -q 1 127.0.0.1 $PORT > $OUT_SELF
sleep 0.1
grep -q "selftest" $OUT_SELF && fail "sender received own message" || pass "sender didn't receive own message"

# ── test 7: no #define ──
grep -q "#define" mini_serv.c && fail "contains #define" || pass "no #define"

# ── cleanup ──
kill $NC1_PID $NC2_PID $NC4_PID $NC5_PID 2>/dev/null
kill $SERVER_PID 2>/dev/null
rm -f $OUT1 $OUT2 $OUT_MSG $OUT_MULTI $OUT_SELF

echo ""
echo "Results: $PASS passed, $FAIL failed"
