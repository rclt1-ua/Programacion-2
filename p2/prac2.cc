#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>


using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

// Registro para las preguntas
struct Question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};


void addQuestion(Database &data, int &numData);






/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch (e){
        case ERR_OPTION:
            cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY:
            cout << "ERROR: empty string" << endl;
            break;
        case ERR_UNIT:
            cout << "ERROR: wrong unit" << endl;
            break;
        case ERR_CHAR:
            cout << "ERROR: wrong char" << endl;
            break;
        case ERR_FILE:
            cout << "ERROR: cannot open file" << endl;
            break;
        case ERR_NAME:
            cout << "ERROR: wrong teacher name" << endl;
            break;
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated name" << endl;
            break;
        case ERR_PASSWORD:
            cout << "ERROR: wrong password" << endl;
            break;      
        case ERR_NO_QUESTIONS:
            cout << "ERROR: no pending questions" << endl;
            break;
        case ERR_ID:
            cout << "ERROR: wrong id" << endl;
            break;
        case ERR_ARGS:
            cout << "ERROR: wrong arguments" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
         << "2- Batch add questions" << endl
         << "3- Delete question" << endl
         << "4- Add teacher" << endl
         << "5- Add answers" << endl
         << "6- View answers" << endl
         << "7- View statistics" << endl
         << "8- Export questions" << endl
         << "q- Quit" << endl
         << "Option: ";
}

// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    int numData = 1;
    data.nextId= numData;
    char option;
    
    do{
        showMenu();
        cin >> option;
        cin.get();
        
        switch(option){
            case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                addQuestion(data, numData);
                break;
            case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                break;
            case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta

                break;
            case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor

                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}

void addQuestion(Database &data, int &numData){
    Question pregunta; // Pregunta a añadir
    string unitStr, // Unidad de la pregunta en formato string
        preguntaStr; // Pregunta a añadir a la base de datos en formato string
    int numero; // Unidad de la pregunta en formato entero
    bool unitCorrecto, // Comprueba si la unidad es correcta
        preguntaCorrecta; // Comprueba si la pregunta es correcta
    

    do{ //-----------------------------------------------------------------------------
        unitCorrecto = false; // Inicializamos la variable a false

        cout << "Enter unit:";
        getline(cin, unitStr);

        if (unitStr.empty()) { // Comprobamos si la unidad está vacía
            error(ERR_EMPTY);
            return;
        }

        try { // Convertimos la unidad a entero
            numero = stoi(unitStr);
            unitCorrecto = true;
        } 
        catch (const std::invalid_argument& e) {// Si no se puede convertir a entero, mostramos un error
            error(ERR_UNIT);
        }

        if(unitCorrecto){// Si la unidad es correcta, comprobamos que esté entre 1 y 5
            if (numero < 1 || numero > 5) { // Comprobamos si la unidad está entre 1 y 5
                error(ERR_UNIT);// Si no está entre 1 y 5, mostramos un error
                unitCorrecto = false;
            }
        }
    } while (!unitCorrecto); // Si la unidad no es correcta, volvemos a pedirla

    if(unitCorrecto){ // Si la unidad es correcta, pedimos la pregunta -----------------------------------------------------------------------------
        do{ // Pedimos la pregunta hasta que sea correcta
            preguntaCorrecta = false;

            cout << "Enter question:";
            getline(cin, preguntaStr);
            
            if(preguntaStr.empty()){ // Comprobamos si la pregunta está vacía
                error(ERR_EMPTY);
                return;
            }

            if(preguntaStr.find("|") != string::npos){ // Comprobamos si la pregunta contiene el carácter '|'
                error(ERR_CHAR); // Si contiene el carácter '|', mostramos un error
            }
            else{
                preguntaCorrecta = true; // Si no contiene el carácter '|', la pregunta es correcta
            }
        }
        while(!preguntaCorrecta); // Si la pregunta no es correcta, volvemos a pedirla

        if(preguntaCorrecta){
            pregunta.id = numData; // Asignamos el id a la pregunta
            pregunta.unit = numero; // Asignamos la unidad a la pregunta
            pregunta.question = preguntaStr; // Asignamos la pregunta a la pregunta
            data.questions.push_back(pregunta); // Añadimos la pregunta a la base de datos
            numData++; // Aumentamos el id para la siguiente pregunta
        }
    }
}


