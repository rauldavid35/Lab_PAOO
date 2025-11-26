#!/usr/bin/env bash
set -e

BUILD_DIR="build"


echo "=========================================="
echo " 🛠️  Configuring & Building Project..."
echo "=========================================="
cmake -S . -B "${BUILD_DIR}"
cmake --build "${BUILD_DIR}" --parallel

set +e 

while true; do
    
    echo ""
    echo "=========================================="
    echo "   MENIU PRINCIPAL - Digital Wallet"
    echo "=========================================="
    echo "  1) Rulare Wallet vechi (Tema anterioara)"
    echo "  2) Rulare Item 13 (Smart Pointers & Crash Demo)"
    echo "  3) Rulare Item 14 (Multithreading & Mutex)"
    echo "  4) Rulare TOATE demo-urile"
    echo "  0) Iesire (Exit)"
    echo "=========================================="
    read -p "Alege o optiune [0-4]: " choice
    echo ""

    case $choice in
        1)
            echo "--> Running Wallet..."
            if [ -f "./wallet" ]; then
                "./wallet"
            else
                echo "Eroare: Executabilul 'wallet' nu a fost gasit."
            fi
            ;;
        2)
            echo "--> Running ITEM 13 (Smart Pointers)..."
            "./${BUILD_DIR}/item13"
            ;;
        3)
            echo "--> Running ITEM 14 (Multithreading)..."
            "./${BUILD_DIR}/item14"
            ;;
        4)
            echo "--> Running ITEM 13..."
            "./${BUILD_DIR}/item13"
            echo ""
            echo "--> Running ITEM 14..."
            "./${BUILD_DIR}/item14"
            ;;
        0)
            echo "Pa pa!"
            exit 0
            ;;
        *)
            echo "Optiune invalida! Alege între 0 si 4."
            ;;
    esac

    echo ""
    echo "----------------------------------------------------"
    read -n 1 -s -r -p "Apasa orice tasta pentru a reveni la meniu..."
    echo ""
done