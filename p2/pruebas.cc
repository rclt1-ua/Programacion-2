   #include <iostream>
   #include <string> // Include the <string> header for getline

   using namespace std;

   int main() {
      int numeroCon; // Declare the variable with the correct data type
      string inputNumero; // Rename the string variable to avoid a naming conflict

      cout << "Numero" << endl;
      getline(cin, inputNumero); // Use the getline function to read input

         if(inputNumero != "1" || inputNumero != "2" || inputNumero != "3" || inputNumero != "4" || inputNumero != "5" || inputNumero != "6" || inputNumero != "7" || inputNumero != "8") {
            cout << "ERROR: wrong option" << endl;
         }
         else if(inputNumero == "1" || inputNumero == "2" || inputNumero == "3" || inputNumero != "4" || inputNumero != "5" || inputNumero != "6" || inputNumero != "7" || inputNumero != "8"){
            numeroCon = stoi(inputNumero); // Convert the string to an integer
            cout << "Numero: " << numeroCon << endl;
         }

   }
