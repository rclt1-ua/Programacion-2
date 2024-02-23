// Programación 2 - Práctica 1
// DNI: A8590323
// Nombre: ROBERTO LOOR TAMAYO


#include <iostream>
#include <vector>

using namespace std;


const int MAXSUBJECT=50;


// Registro para las fechas
struct Date{
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};


void addAcademicYear(vector<AcademicYear> &listYears);
void deleteAcademicYear(vector<AcademicYear> &listYears);
void addTeacher(vector<AcademicYear> &listYears);
void deleteTeacher(vector<AcademicYear> &listYears);
void showTeacher(vector<AcademicYear> &listYears);
void addPhrase(vector<AcademicYear> &listYears);
void summary(vector<AcademicYear> &listYears);

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_DUPLICATED: cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING: cout << "ERROR: number out of range" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add academic year" << endl
         << "2- Delete academic year" << endl
         << "3- Add teacher" << endl
         << "4- Delete teacher" << endl
         << "5- Show teacher" << endl
         << "6- Add phrase" << endl
         << "7- Summary" << endl
         << "q- Quit" << endl
         << "Option: ";
}

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<AcademicYear> listYears;

    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                addAcademicYear(listYears);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                deleteAcademicYear(listYears);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                addTeacher(listYears);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                deleteTeacher(listYears);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                showTeacher(listYears); 
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                addPhrase(listYears);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                summary(listYears);
                break;
            case 'q': 
                break;
            case 'Q': 
                break;
            default: 
                error(ERR_OPTION);
        }
    }while(option!='q');
}



//Funcion para añadir un anyo academico
void addAcademicYear(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // LARGO DE LA LISTA DE ANYOS
        encontrado = -1, // VARIABLE PARA SABER SI EL ANYO YA EXISTE
        recorredor; // RECORREDOR PARA EL FOR
    string idY; // VARIABLE PARA AÑADIR EL ANYO
    int idYInt; // VARIABLE PARA AÑADIR EL ANYO EN ENTERO
    AcademicYear anyo; // VARIABLE PARA AÑADIR EL ANYO
    

    cout<< "Introduce el año del curso académico: " << endl;
    getline(cin, idY);



    if(largo ==0){ // SI NO SE ENCUENTRA NINGUN ANYO, SE AGREGA DIRECTAMENTE EL ANYO
        idYInt = stoi(idY);
        anyo.id = idYInt;
        listYears.push_back(anyo);
    } 

    if(idY.empty()){ // SI NO SE INTRODUCE NINGUN ANYO, SE MUESTRA UN ERROR
        error(ERR_EMPTY);
        cout << endl;
    }
    else{ // SI HAY DATOS, SE COMPRUEBA QUE NO EXISTA EL ANYO DENTRO DEL VECTOR
        idYInt = stoi(idY);

        for(recorredor = 0; recorredor < largo && !encontrado == -1; recorredor++){
            if(listYears[recorredor].id == idYInt){
                encontrado = 1; // SI SE ENCUENTRA EL ANYO, SE CAMBIA EL VALOR DE LA VARIABLE PARA SABER QUE YA EXISTE
            }
        }

        if(encontrado == 1){ // SI SE ENCUENTRA EL ANYO, SE MUESTRA UN ERROR
            error(ERR_DUPLICATED);
            cout << endl;
        }
        else{ // SI NO SE ENCUENTRA EL ANYO, SE AGREGA EL ANYO
            anyo.id = idYInt;
            listYears.push_back(anyo);
        }
    }
}


void addAcademicYear(vector<AcademicYear> *listYears){
    int largo = listYears->size(), // LARGO DE LA LISTA DE ANYOS
        encontrado = -1, // VARIABLE PARA SABER SI EL ANYO YA EXISTE
        recorredor; // IDY PARA EL ID ANYO Y RECORREDOR PARA EL FOR
    string idY;
    int idYInt;
    AcademicYear anyo; // VARIABLE PARA AÑADIR EL ANYO
    

    cout<< "Introduce el año del curso académico: " << endl;
    getline(cin, idY);


    if(largo ==0){ // SI NO SE ENCUENTRA NINGUN ANYO, SE AGREGA DIRECTAMENTE EL ANYO
        idYInt = stoi(idY);
        anyo.id = idYInt;
        listYears->push_back(anyo);
    } 

    if(idY.empty()){ // SI NO SE INTRODUCE NINGUN ANYO, SE MUESTRA UN ERROR
        error(ERR_EMPTY);
        cout << endl;
    }
    else{ // SI HAY DATOS, SE COMPRUEBA QUE NO EXISTA EL ANYO DENTRO DEL VECTOR
        idYInt = stoi(idY); // CONVERTIR DE STRING A ENTERO

        for(recorredor = 0; recorredor < largo && !encontrado == -1; recorredor++){
            if((*listYears)[recorredor].id == idYInt) {
                encontrado = 1; // SI SE ENCUENTRA EL ANYO, SE CAMBIA EL VALOR DE LA VARIABLE PARA SABER QUE YA EXISTE
            }
        }

        if(encontrado == 1){ // SI SE ENCUENTRA EL ANYO, SE MUESTRA UN ERROR
            error(ERR_DUPLICATED);
            cout << endl;
        }
        else{ // SI NO SE ENCUENTRA EL ANYO, SE AGREGA EL ANYO
            anyo.id = idYInt;
            listYears->push_back(anyo);
        }
    }
}