#include <iostream>
#include "tcomplejo.h"

using namespace std;

int main() {
    // 1. PROBAR CONSTRUCTORES
    cout << "--- Probando Constructores ---" << endl;
    TComplejo cDefault;           // (0,0)
    TComplejo cReal(5.0);         // (5,0)
    TComplejo cCompleto(3.0, 4.0);// (3,4)
    TComplejo cCopia(cCompleto);  // (3,4) copia

    // 2. PROBAR GETTERS Y SETTERS
    cout << "C1 (Default): " << cDefault.Re() << " " << cDefault.Im() << endl;
    cDefault.Re(10.5);
    cDefault.Im(2.5);
    cout << "C1 (Modificado): " << cDefault.Re() << " " << cDefault.Im() << endl;

    // 3. PROBAR ARITMÉTICA (Complejo + Complejo)
    cout << "\n--- Probando Aritmetica entre Complejos ---" << endl;
    TComplejo cA(1, 2);
    TComplejo cB(3, 4);
    TComplejo cSuma = cA + cB;
    TComplejo cResta = cA - cB;
    TComplejo cMult = cA * cB;

    cout << "Suma (1,2) + (3,4): (" << cSuma.Re() << " " << cSuma.Im() << ")" << endl;
    cout << "Resta (1,2) - (3,4): (" << cResta.Re() << " " << cResta.Im() << ")" << endl;
    cout << "Mult (1,2) * (3,4): (" << cMult.Re() << " " << cMult.Im() << ")" << endl;

    // 4. PROBAR ARITMÉTICA (con Double)
    cout << "\n--- Probando Aritmetica con Doubles ---" << endl;
    TComplejo cD = cA + 10.0; // Complejo + Double
    TComplejo cE = 10.0 + cA; // Double + Complejo (Friend)
    
    cout << "(1,2) + 10.0: (" << cD.Re() << " " << cD.Im() << ")" << endl;
    cout << "10.0 + (1,2): (" << cE.Re() << " " << cE.Im() << ")" << endl;

    // 5. PROBAR MÓDULO Y ARGUMENTO
    cout << "\n--- Probando Modulo y Argumento ---" << endl;
    TComplejo cM(3, 4); // El módulo debería ser 5 (3-4-5 pitagórico)
    cout << "Modulo de (3,4): " << cM.Mod() << endl;
    cout << "Argumento de (3,4): " << cM.Arg() << " rad" << endl;

    // 6. PROBAR COMPARACIONES
    cout << "\n--- Probando Comparaciones ---" << endl;
    TComplejo c1(1, 1), c2(1, 1), c3(2, 2);
    cout << "¿(1,1) == (1,1)?: " << (c1 == c2 ? "SI" : "NO") << endl;
    cout << "¿(1,1) != (2,2)?: " << (c1 != c3 ? "SI" : "NO") << endl;

    // 7. PROBAR ASIGNACIÓN
    cout << "\n--- Probando Asignacion ---" << endl;
    TComplejo cAsig;
    cAsig = c3;
    cout << "C_asig despues de cAsig = c3: (" << cAsig.Re() << " " << cAsig.Im() << ")" << endl;

    return 0;
}