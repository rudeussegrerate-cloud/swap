#!/bin/bash

echo "========== TEST SUITE COMPLÈTE =========="
echo ""

# Test 1: Arguments valides simples
echo "1. Arguments simples séparés"
./push_swap 5 4 3 2 1 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 2: Chaîne simple sans flags
echo "2. Chaîne simple sans flags"
./push_swap "5 4 3 2 1" > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 3: Flag --simple avec arguments séparés
echo "3. Flag --simple avec arguments séparés"
./push_swap --simple 5 4 3 2 1 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 4: Flag --medium avec arguments séparés
echo "4. Flag --medium avec arguments séparés"
./push_swap --medium 5 4 3 2 1 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 5: Flag --complex avec arguments séparés
echo "5. Flag --complex avec arguments séparés"
./push_swap --complex 5 4 3 2 1 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 6: Flag --bench avec arguments séparés
echo "6. Flag --bench avec arguments séparés"
./push_swap --bench 5 4 3 2 1 2>&1 | grep -q "bench" && echo "✓ PASS" || echo "✗ FAIL"

# Test 7: Chaîne avec flag dans la chaîne
echo "7. Chaîne avec flag dans la chaîne"
./push_swap "5 4 --simple 3 2" > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 8: Chaîne avec --bench dans la chaîne
echo "8. Chaîne avec --bench dans la chaîne"
./push_swap "5 4 --bench 3" 2>&1 | grep -q "bench" && echo "✓ PASS" || echo "✗ FAIL"

# Test 9: Chaîne avec flag et --bench
echo "9. Chaîne avec flag et --bench"
./push_swap "5 4 --simple 3 --bench" 2>&1 | grep -q "bench" && echo "✓ PASS" || echo "✗ FAIL"

# Test 10: Flag en avant, chaîne avec --bench
echo "10. Flag en avant, chaîne avec --bench"
./push_swap --medium "5 4 3 --bench" 2>&1 | grep -q "bench" && echo "✓ PASS" || echo "✗ FAIL"

# Test 11: --bench séparé, chaîne avec flag
echo "11. --bench séparé, chaîne avec flag"
./push_swap --bench "5 4 --simple 3" 2>&1 | grep -q "bench" && echo "✓ PASS" || echo "✗ FAIL"

# Test 12: Flag invalide (doit échouer)
echo "12. Flag invalide --invalid (doit échouer)"
./push_swap --invalid 5 4 3 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 13: Flag invalide dans chaîne (doit échouer)
echo "13. Flag invalide dans chaîne (doit échouer)"
./push_swap "5 --invalid 4" 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 14: Deux flags dupliqués (doit échouer)
echo "14. Deux flags dupliqués (doit échouer)"
./push_swap --simple --simple 5 4 3 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 15: Deux flags différents (doit échouer)
echo "15. Deux flags différents (doit échouer)"
./push_swap --simple --medium 5 4 3 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 16: Deux flags dans chaîne (doit échouer)
echo "16. Deux flags dans chaîne (doit échouer)"
./push_swap "5 --simple --medium 4" 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 17: Pas d'arguments
echo "17. Pas d'arguments"
./push_swap 2>&1 > /dev/null; [ $? -eq 1 ] && echo "✓ PASS" || echo "✗ FAIL"

# Test 18: Aucun nombre (que flags)
echo "18. Aucun nombre (que flags)"
./push_swap --simple --bench 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 19: Chiffre unique
echo "19. Chiffre unique"
./push_swap 5 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 20: Deux chiffres
echo "20. Deux chiffres"
./push_swap 5 4 > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 21: Nombres négatifs
echo "21. Nombres négatifs"
./push_swap "-5 -4 -3 -2" > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 22: Zéro
echo "22. Zéro inclus"
./push_swap "5 0 3" > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 23: Nombre très grand
echo "23. Nombre très grand"
./push_swap "2147483647 1 0" > /dev/null && echo "✓ PASS" || echo "✗ FAIL"

# Test 24: Doublon (doit échouer)
echo "24. Doublon (doit échouer)"
./push_swap "5 5 3" 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

# Test 25: Chaîne vide
echo "25. Chaîne vide"
./push_swap "" 2>&1 | grep -q "Error" && echo "✓ PASS" || echo "✗ FAIL"

echo ""
echo "========== FIN DES TESTS =========="
