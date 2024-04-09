   #include <iostream>
   #include <string> // Include the <string> header for getline

   using namespace std;

   int main() {
      int numeroCon; // Declare the variable with the correct data type
      string inputNumero; // Rename the string variable to avoid a naming conflict

      cout << "Numero" << endl;
      getline(cin, inputNumero); // Use the getline function to read input

      numeroCon = stoi(inputNumero); // Convert the string to an integer

   }
