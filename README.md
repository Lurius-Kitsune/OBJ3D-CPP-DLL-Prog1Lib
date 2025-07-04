# OBJ3D‑CPP‑DLL‑Prog1Lib

📦 **Bibliothèque C++ pour gestion d’objets 3D sous forme de DLL**

---

## 📜 Description

Ce projet est une **bibliothèque dynamique (DLL)** en C++, développée par des étudiants en **1ʳʳ année de programmation** à **Objectif 3D**.
Elle permet de gérer, charger et manipuler des objets 3D (format `.obj`) et peut être intégrée facilement dans d’autres applications via un lien dynamique.

---

## 🚀 Fonctionnalités principales

* Chargement de fichiers `.obj`
* Extraction des données de vertices, normales et UV
* Interface C++ simple et claire pour accéder aux données 3D
* Compilation en DLL pour usage modulaire
* Exemple d’utilisation inclus

---

## 📦 Structure du projet

```
OBJ3D-CPP-DLL-Prog1Lib/
├── include/          ← Headers publics de la DLL
├── src/              ← Code source de la bibliothèque
├── example/          ← Projet de démonstration
├── CMakeLists.txt    ← Script CMake pour compilation
└── README.md         ← Ce fichier
```

---

## 🛠️ Prérequis

* Compilateur C++ (GCC, Clang, Visual Studio…)
* [CMake](https://cmake.org) 3.15 ou supérieur
* Plateforme : Windows, Linux ou macOS

---

## ⚙️ Compilation

1. Clonez le dépôt :

   ```bash
   git clone https://github.com/Lurius-Kitsune/OBJ3D-CPP-DLL-Prog1Lib.git
   cd OBJ3D-CPP-DLL-Prog1Lib
   ```

2. Créez un dossier de build et compilez :

   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

3. (Optionnel) Lancez l’exemple :

   ```bash
   cd example
   ./Prog1LibExample   # ou Prog1LibExample.exe sous Windows
   ```

---

## 🧹 Intégration dans un projet externe

1. Incluez les headers (`include/`) dans votre projet.
2. Liez la DLL générée à votre exécutable.
3. Exemple d’utilisation :

   ```cpp
   #include "OBJ3DLoader.h"

   int main() {
       OBJ3DLoader loader("monObjet.obj");
       auto vertices = loader.getVertices();
       // Utilisation des données...
       return 0;
   }
   ```

---

## 🧪 Tests

* Un projet d’exemple dans `example/` permet de tester la DLL.
* Le système de build vérifie que la DLL est bien générée.

---

## 📝 Remarques

> ⚠️ Ce projet a été réalisé **par des étudiants de 1ʳʳ année à Objectif 3D**
> Il est avant tout **pédagogique**, et ne vise pas à être une solution de production.

---

## 📬 Contact

* Auteurs : Étudiants Objectif 3D (1ʳʳ année)
* Pour toute question, utilisez les issues GitHub

---

## 🗞 Licence

> Licence à définir (MIT, GPL, etc.) — selon le choix des auteurs ou de l’école.
