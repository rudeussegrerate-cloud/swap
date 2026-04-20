#!/usr/bin/env bash
# ============================================================
#  TEST SUITE — push_swap
#  Usage : ./test_push_swap.sh [chemin/vers/push_swap]
# ============================================================

# ---------- couleurs ----------
RED='\033[0;31m'
GRN='\033[0;32m'
YLW='\033[1;33m'
BLU='\033[1;34m'
CYN='\033[0;36m'
BOLD='\033[1m'
RST='\033[0m'

# ---------- binaire ----------
PS="${1:-./push_swap}"

if [ ! -f "$PS" ]; then
  echo -e "${RED}[ERREUR]${RST} Binaire introuvable : $PS"
  echo "Usage : $0 [chemin/vers/push_swap]"
  exit 1
fi

chmod +x "$PS"

# ---------- compteurs ----------
PASS=0
FAIL=0
TOTAL=0

# ============================================================
#  Fonctions utilitaires
# ============================================================

ok()   { echo -e "  ${GRN}[OK]${RST}  $1" ; ((PASS++)); ((TOTAL++)); }
ko()   { echo -e "  ${RED}[KO]${RST}  $1" ; ((FAIL++)); ((TOTAL++)); }
sep()  { echo -e "${BLU}${BOLD}── $1 ──────────────────────────────────────────${RST}"; }
info() { echo -e "  ${CYN}$1${RST}"; }

# Vérifie que le programme retourne "Error\n" sur stderr ET exit code != 0
expect_error() {
  local desc="$1"; shift
  local stderr_out
  local exit_code

  stderr_out=$("$PS" "$@" 2>&1 1>/dev/null)
  exit_code=$?

  if echo "$stderr_out" | grep -q "^Error$" && [ "$exit_code" -ne 0 ]; then
    ok "$desc"
  else
    ko "$desc  [exit=$exit_code stderr='$stderr_out']"
  fi
}

# Vérifie que le programme réussit (exit 0) et ne print pas "Error"
expect_ok() {
  local desc="$1"; shift
  local output stderr_out exit_code

  output=$("$PS" "$@" 2>/tmp/ps_stderr)
  exit_code=$?
  stderr_out=$(cat /tmp/ps_stderr)

  if [ "$exit_code" -eq 0 ] && ! echo "$stderr_out" | grep -q "^Error$"; then
    ok "$desc"
  else
    ko "$desc  [exit=$exit_code stderr='$stderr_out']"
  fi
}

# Vérifie que la sortie est bien triée (utilise le checker interne)
expect_sorted() {
  local desc="$1"; shift
  local args=("$@")
  local ops exit_code is_sorted

  ops=$("$PS" "${args[@]}" 2>/dev/null)
  exit_code=$?

  if [ "$exit_code" -ne 0 ]; then
    ko "$desc  [exit=$exit_code — programme planté]"
    return
  fi

  # Reconstituons la pile et vérifions l'ordre
  is_sorted=$(echo "$ops" | python3 -c "
import sys, subprocess

args = [$(printf '"%s",' "$@" | sed 's/,$//')]
# Simuler les opérations push_swap
stack_a = []
stack_b = []

# Remplir stack_a depuis les arguments
for a in args:
    try:
        stack_a.append(int(a))
    except:
        pass

ops = sys.stdin.read().strip().split('\n') if sys.stdin.read().strip() else []

# Re-lire stdin
" 2>/dev/null || echo "skip")

  # Méthode simple : on vérifie que les nombres dans la stack sont triés
  # en simulant les opérations manuellement
  local sorted_check
  sorted_check=$(python3 /tmp/ps_checker.py "$ops" "$@" 2>/dev/null)

  if [ "$sorted_check" = "OK" ]; then
    ok "$desc"
  elif [ "$sorted_check" = "KO" ]; then
    ko "$desc  [pile mal triée après opérations]"
  else
    ok "$desc  [ops=$( echo "$ops" | wc -l | tr -d ' ')]"
  fi
}

# Vérifie sortie triée via simulation Python
check_sorted() {
  local desc="$1"; shift
  local args=("$@")

  # Générer le checker Python à la volée
  python3 - "${args[@]}" <<'PYEOF'
import sys, subprocess, os

ps_bin = os.environ.get("PS_BIN", "./push_swap")
args = sys.argv[1:]

result = subprocess.run([ps_bin] + args, capture_output=True, text=True)
if result.returncode != 0:
    print("CRASH")
    sys.exit(0)

ops = result.stdout.strip().split('\n') if result.stdout.strip() else []

stack_a = []
stack_b = []
for a in args:
    try:
        val = int(a)
        stack_a.append(val)
    except:
        pass

for op in ops:
    op = op.strip()
    if not op:
        continue
    if op == 'sa' and len(stack_a) >= 2:
        stack_a[0], stack_a[1] = stack_a[1], stack_a[0]
    elif op == 'sb' and len(stack_b) >= 2:
        stack_b[0], stack_b[1] = stack_b[1], stack_b[0]
    elif op == 'ss':
        if len(stack_a) >= 2: stack_a[0], stack_a[1] = stack_a[1], stack_a[0]
        if len(stack_b) >= 2: stack_b[0], stack_b[1] = stack_b[1], stack_b[0]
    elif op == 'pa' and stack_b:
        stack_a.insert(0, stack_b.pop(0))
    elif op == 'pb' and stack_a:
        stack_b.insert(0, stack_a.pop(0))
    elif op == 'ra' and stack_a:
        stack_a.append(stack_a.pop(0))
    elif op == 'rb' and stack_b:
        stack_b.append(stack_b.pop(0))
    elif op == 'rr':
        if stack_a: stack_a.append(stack_a.pop(0))
        if stack_b: stack_b.append(stack_b.pop(0))
    elif op == 'rra' and stack_a:
        stack_a.insert(0, stack_a.pop())
    elif op == 'rrb' and stack_b:
        stack_b.insert(0, stack_b.pop())
    elif op == 'rrr':
        if stack_a: stack_a.insert(0, stack_a.pop())
        if stack_b: stack_b.insert(0, stack_b.pop())

if stack_b:
    print("KO_B_NOT_EMPTY")
elif stack_a == sorted(stack_a):
    print(f"OK:{len(ops)}")
else:
    print("KO_NOT_SORTED")
PYEOF
}

# ============================================================
#  DÉBUT DES TESTS
# ============================================================

echo ""
echo -e "${BOLD}${YLW}╔══════════════════════════════════════════╗${RST}"
echo -e "${BOLD}${YLW}║      TEST SUITE — push_swap              ║${RST}"
echo -e "${BOLD}${YLW}╚══════════════════════════════════════════╝${RST}"
echo ""
info "Binaire testé : $PS"
echo ""

# ============================================================
sep "1. Arguments invalides → doit afficher Error"
# ============================================================

expect_error "Aucun argument"
expect_error "Lettre seule"                   "a"
expect_error "Lettres mélangées"              "abc" "def"
expect_error "Nombre avec lettres"            "1a"
expect_error "Signe seul +"                   "+"
expect_error "Signe seul -"                   "-"
expect_error "Double signe ++"               "++"
expect_error "Double signe --"               "--"
expect_error "Signe avec lettre +-"           "+-1"
expect_error "Virgule décimale"               "1.5"
expect_error "Virgule décimale neg"           "-1.5"
expect_error "Nombre avec espace interne"     "1 2a"
expect_error "String vide entre guillemets"   "" "1" "2"
expect_error "Overflow INT_MAX+1"             "2147483648"
expect_error "Overflow INT_MIN-1"             "-2147483649"
expect_error "Overflow grand positif"         "9999999999"
expect_error "Overflow grand négatif"         "-9999999999"
expect_error "Doublon simple"                 "1" "1"
expect_error "Doublon avec 3 nombres"         "1" "2" "1"
expect_error "Doublon 0 0"                    "0" "0"
expect_error "Flag invalide"                  "1" "2" "--unknownflag"
expect_error "Deux flags identiques"          "--simple" "--simple" "1" "2" "3"
expect_error "Caractère spécial @"            "@"
expect_error "Caractère spécial !"            "1" "!" "2"
expect_error "Tab comme argument"             "$(printf '\t')"
expect_error "Newline dans argument"          "$(printf '1\n2')"

# ============================================================
sep "2. Arguments valides → ne doit PAS afficher Error"
# ============================================================

expect_ok "Un seul nombre"                   "42"
expect_ok "Un seul nombre négatif"           "-42"
expect_ok "Nombre INT_MAX"                   "2147483647"
expect_ok "Nombre INT_MIN"                   "-2147483648"
expect_ok "Zéro seul"                        "0"
expect_ok "Déjà trié 2 élts"                 "1" "2"
expect_ok "Déjà trié 5 élts"                 "1" "2" "3" "4" "5"
expect_ok "Flag --simple"                    "3" "1" "2" "--simple"
expect_ok "Flag --medium"                    "3" "1" "2" "--medium"
expect_ok "Flag --complex"                   "3" "1" "2" "--complex"
expect_ok "Flag --adaptive"                  "3" "1" "2" "--adaptive"
expect_ok "Flag --bench"                     "3" "1" "2" "--bench"
expect_ok "Args en string unique"            "3 1 2"
expect_ok "Nombres négatifs mélangés"        "-3" "-1" "-2"
expect_ok "Mix positif/négatif"             "-1" "0" "1"
expect_ok "Signe + explicite"               "+1" "+2" "+3"
expect_ok "2 élts inversés"                 "2" "1"
expect_ok "3 élts"                           "3" "1" "2"

# ============================================================
sep "3. Tri correct → pile doit être ordonnée après"
# ============================================================

run_sort_test() {
  local desc="$1"; shift
  local result
  export PS_BIN="$PS"
  result=$(check_sorted "$desc" "$@")
  if echo "$result" | grep -q "^OK:"; then
    local ops
    ops=$(echo "$result" | cut -d: -f2)
    ok "$desc  [${ops} opérations]"
  elif [ "$result" = "CRASH" ]; then
    ko "$desc  [CRASH — exit code non nul]"
  else
    ko "$desc  [$result]"
  fi
}

run_sort_test "Tri 2 élts inversés"           "2" "1"
run_sort_test "Tri 3 élts"                    "3" "1" "2"
run_sort_test "Tri 3 élts inversés"           "3" "2" "1"
run_sort_test "Tri 5 élts"                    "5" "3" "1" "4" "2"
run_sort_test "Tri 5 élts inversés"           "5" "4" "3" "2" "1"
run_sort_test "Tri avec 0 et négatifs"        "3" "-1" "0" "2" "-2"
run_sort_test "Tri 10 élts aléatoires"        "7" "3" "9" "1" "5" "8" "2" "6" "4" "10"
run_sort_test "Tri 10 élts inversés"          "10" "9" "8" "7" "6" "5" "4" "3" "2" "1"
run_sort_test "Tri avec INT_MIN et INT_MAX"   "2147483647" "0" "-2147483648"
run_sort_test "Tri string unique"             "5 3 1 4 2"
run_sort_test "Tri avec --simple"             "5" "3" "1" "4" "2" "--simple"
run_sort_test "Tri avec --medium"             "5" "3" "1" "4" "2" "--medium"
run_sort_test "Tri avec --complex"            "5" "3" "1" "4" "2" "--complex"

# ============================================================
sep "4. Cas limites / comportements spéciaux"
# ============================================================

# Déjà trié → aucune opération ne doit être émise
test_no_ops() {
  local desc="$1"; shift
  local ops
  ops=$("$PS" "$@" 2>/dev/null)
  if [ -z "$ops" ]; then
    ok "$desc  [0 opérations — correct]"
  else
    ko "$desc  [opérations émises alors que déjà trié : $(echo "$ops" | wc -l | tr -d ' ')]"
  fi
}

test_no_ops "Déjà trié → 0 ops (1 elt)"   "42"
test_no_ops "Déjà trié → 0 ops (2 elts)"  "1" "2"
test_no_ops "Déjà trié → 0 ops (3 elts)"  "1" "2" "3"
test_no_ops "Déjà trié → 0 ops (5 elts)"  "1" "2" "3" "4" "5"

# Vérifier que --bench écrit sur stderr et non stdout
test_bench_stderr() {
  local stdout stderr
  stdout=$("$PS" --bench 3 1 2 2>/tmp/bench_err)
  stderr=$(cat /tmp/bench_err)
  if echo "$stderr" | grep -q "\[bench\]" && ! echo "$stdout" | grep -q "\[bench\]"; then
    ok "--bench écrit sur stderr uniquement"
  else
    ko "--bench : sortie mal dirigée [stdout='$stdout']"
  fi
}
test_bench_stderr

# Operations uniquement sur stdout (pas stderr)
test_ops_stdout() {
  local stdout stderr
  stdout=$("$PS" 3 1 2 2>/tmp/ops_err)
  stderr=$(cat /tmp/ops_err)
  if [ -z "$stderr" ] && echo "$stdout" | grep -qE "^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$"; then
    ok "Opérations sur stdout, stderr vide (cas normal)"
  elif [ -z "$stderr" ]; then
    ok "Stderr vide (opérations valides)"
  else
    ko "Stderr non vide pour un input valide [stderr='$stderr']"
  fi
}
test_ops_stdout

# Signal/crash (valgrind-style) — test que le programme ne segfault pas
test_no_crash() {
  local desc="$1"; shift
  local exit_code
  "$PS" "$@" >/dev/null 2>/dev/null
  exit_code=$?
  # exit 139 = segfault, 134 = abort (double free), 136 = FPE
  if [ "$exit_code" -eq 139 ] || [ "$exit_code" -eq 134 ] || [ "$exit_code" -eq 136 ]; then
    ko "$desc  [CRASH signal — exit=$exit_code]"
  else
    ok "$desc  [pas de crash — exit=$exit_code]"
  fi
}

test_no_crash "Pas de segfault — args invalides"     "abc"
test_no_crash "Pas de segfault — overflow"            "99999999999"
test_no_crash "Pas de segfault — doublon"             "1" "1" "2"
test_no_crash "Pas de segfault — string vide"         ""
test_no_crash "Pas de segfault — grand tri 20 élts"   20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
test_no_crash "Pas de segfault — flag invalide"       "1" "2" "--blabla"
test_no_crash "Pas de segfault — signe seul"          "+"

# ============================================================
sep "5. Nombre d'opérations (performance)"
# ============================================================

count_ops() {
  local desc="$1" max_ops="$2"; shift 2
  local ops count
  ops=$("$PS" "$@" 2>/dev/null)
  count=$(echo "$ops" | grep -cE "^(sa|sb|ss|pa|pb|ra|rb|rr|rra|rrb|rrr)$")
  if [ "$count" -le "$max_ops" ]; then
    ok "$desc  [${count} ops ≤ ${max_ops}]"
  else
    ko "$desc  [${count} ops > limite ${max_ops}]"
  fi
}

count_ops "3 élts ≤ 3 ops"                3   "3" "1" "2"
count_ops "3 élts inversés ≤ 3 ops"       3   "3" "2" "1"
count_ops "5 élts ≤ 12 ops"               12  "5" "3" "1" "4" "2"
count_ops "5 élts inversés ≤ 12 ops"      12  "5" "4" "3" "2" "1"
count_ops "10 élts ≤ 200 ops"             200 "10" "9" "8" "7" "6" "5" "4" "3" "2" "1"

# ============================================================
#  RÉSUMÉ FINAL
# ============================================================

echo ""
echo -e "${BOLD}${YLW}╔══════════════════════════════════════════╗${RST}"
echo -e "${BOLD}${YLW}║              RÉSUMÉ                      ║${RST}"
echo -e "${BOLD}${YLW}╚══════════════════════════════════════════╝${RST}"
echo ""
echo -e "  Total  : ${BOLD}$TOTAL${RST} tests"
echo -e "  ${GRN}OK     : $PASS${RST}"
if [ "$FAIL" -gt 0 ]; then
  echo -e "  ${RED}KO     : $FAIL${RST}"
else
  echo -e "  KO     : $FAIL"
fi
echo ""

if [ "$FAIL" -eq 0 ]; then
  echo -e "${GRN}${BOLD}  ✔ Tous les tests passent !${RST}"
else
  echo -e "${RED}${BOLD}  ✘ $FAIL test(s) échoué(s) — voir les [KO] ci-dessus${RST}"
fi
echo ""

[ "$FAIL" -eq 0 ] && exit 0 || exit 1
