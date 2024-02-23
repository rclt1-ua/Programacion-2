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



//FUNCION PARA AÑADIR UN CURSO ACADEMICO
void addAcademicYear(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        encontrado = -1, // Variable para saber si se ha encontrado el curso académico
        recorredor, // Variable para recorrer el vector
        idYInt; // Variable para el año del curso académico en entero
    string idY; // Variable para el año del curso académico en string
    AcademicYear anyo; // Variable para el curso académico
    

    cout<< "Introduce el año del curso académico: " << endl;
    getline(cin, idY); // Se introduce el año del curso académico con getline para evitar problemas con el buffer de teclado



    if(largo ==0){ // Si el vector está vacío, se añade el curso académico
        idYInt = stoi(idY); // Se convierte el año del curso académico a entero
        anyo.id = idYInt; // Se añade el año del curso académico al registro
        listYears.push_back(anyo); // Se añade el curso académico al vector
    } 

    if(idY.empty()){ // Si el año del curso académico está vacío, se muestra un mensaje de error
        error(ERR_EMPTY); // Se muestra un mensaje de error
        cout << endl; // Se imprime un salto de línea para mejorar la legibilidad
    }
    else{ // Si el año del curso académico no está vacío, se comprueba si ya existe
        idYInt = stoi(idY); // Se convierte el año del curso académico a entero

        for(recorredor = 0; recorredor < largo && !encontrado == -1; recorredor++){ // Se recorre el vector para comprobar si ya existe el curso académico
            if(listYears[recorredor].id == idYInt){ // Si ya existe el curso académico, se cambia el valor de la variable "encontrado"
                encontrado = 1; // Se cambia el valor de la variable encontrado
            }
        }

        if(encontrado == 1){ // Si ya existe el curso académico, se muestra un mensaje de error
            error(ERR_DUPLICATED); // Se muestra un mensaje de error
            cout << endl; // Se imprime un salto de línea para mejorar la legibilidad
        }
        else{ 
            anyo.id = idYInt; // Se añade el año del curso académico al registro
            listYears.push_back(anyo); // Se añade el curso académico al vector
        }
    }
}



//FUNCION PARA AÑADIR UN CURSO ACADEMICO CON PUNTEROS
void addAcademicYear(vector<AcademicYear> *listYears){
    int largo = listYears->size(), // Tamaño del vector
        encontrado = -1, // Variable para saber si se ha encontrado el curso académico
        recorredor, // Variable para recorrer el vector
        idYInt; // Variable para el año del curso académico en entero
    string idY; // Variable para el año del curso académico en string
    AcademicYear anyo; // Variable para el curso académico
    

    cout<< "Introduce el año del curso académico: " << endl;
    getline(cin, idY);


    if(largo ==0){ // Si el vector está vacío, se añade el curso académico
        idYInt = stoi(idY); // Se convierte el año del curso académico a entero
        anyo.id = idYInt; // Se añade el año del curso académico al registro
        listYears->push_back(anyo); // Se añade el curso académico al vector
    } 

    if(idY.empty()){ // Si el año del curso académico está vacío, se muestra un mensaje de error
        error(ERR_EMPTY); // Se muestra un mensaje de error
        cout << endl; // Se imprime un salto de línea para mejorar la legibilidad
    }
    else{  // Si el año del curso académico no está vacío, se comprueba si ya existe
        idYInt = stoi(idY); // Se convierte el año del curso académico a entero

        for(recorredor = 0; recorredor < largo && !encontrado == -1; recorredor++){ // Se recorre el vector para comprobar si ya existe el curso académico
            if((*listYears)[recorredor].id == idYInt) { // Si ya existe el curso académico, se cambia el valor de la variable "encontrado"
                encontrado = 1; // Se cambia el valor de la variable encontrado
            }
        }

        if(encontrado == 1){ // Si ya existe el curso académico, se muestra un mensaje de error
            error(ERR_DUPLICATED); // Se muestra un mensaje de error
            cout << endl; // Se imprime un salto de línea para mejorar la legibilidad
        }
        else{ // Si no existe el curso académico, se añade al vector
            anyo.id = idYInt; // Se añade el año del curso académico al registro
            listYears->push_back(anyo); // Se añade el curso académico al vector

            cout << endl << "Year added" << endl << endl; // Se muestra un mensaje de éxito
        }
    }
}



//FUNCION PARA ELIMINAR UN CURSO ACADEMICO
void deleteAcademicYear(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        eliminado = -1, // Variable para saber si se ha eliminado el curso académico
        seIntrodujo = 1, // Variable para saber si se ha introducido un valor
        recorredor, // Variable para recorrer el vector
        idYInt; // Variable para el año del curso académico en entero
    string idY; // Variable para el año del curso académico en string


    do{ 
        cout<< "Enter academic year: " << endl;
        cin >> idY;

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
            error(ERR_NOT_EXIST); // Se muestra un mensaje de error
        }

        if(idY.empty()){ // Si el año del curso académico pedido está vacío, se muestra un mensaje de error
            error(ERR_EMPTY); // Se muestra un mensaje de error
            seIntrodujo = -1; // Se cambia el valor de la variable "seIntrodujo"  
        }    
        else{ // Si el año del curso académico pedido no está vacío, se comprueba si existe
            seIntrodujo = 1; // Se cambia el valor de la variable "seIntrodujo"

            idYInt = stoi(idY); // Se convierte el año del curso académico a entero

            for(int recorredor = 0; recorredor < largo && eliminado == -1; recorredor++){ // Se recorre el vector para comprobar si existe el curso académico
                if(listYears[recorredor].id == idYInt){ // Si existe el curso académico, se elimina
                    listYears.erase(listYears.begin() + recorredor); // Se elimina el curso académico del vector

                    eliminado = 1; // Se cambia el valor de la variable "eliminado"

                    cout << endl << "Year deleted" << endl << endl; // Se muestra un mensaje de éxito
                }
            }
            
            if(eliminado == -1){ // Si no existe el curso académico, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            }
        }
    } 
    while(eliminado == -1 && seIntrodujo == 1); // Mientras no se haya eliminado el curso académico y se haya introducido un valor
}



//FUNCION PARA AÑADIR UN PROFESOR
void addTeacher(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        seIntrodujo = 1, // Variable para saber si se ha introducido un valor
        salir = 0, // Variable para salir del bucle. Salir 1 para salir por error, salir 2 para salir por éxito
        idYInt, // Variable para el año del curso académico en entero
        recorredor, // Variable para recorrer el vector
        recorredor2; // Variable para recorrer el vector
    float puntuacionFl; // Variable para la puntuación del profesor
    string nombre, asignatura, apodo, idY, puntuacion; // Variables para el nombre, asignatura, apodo, año del curso académico y puntuación del profesor
    Teacher profesor; // Variable para el profesor
    
    do{ // Bucle para introducir el año del curso académico
        cout<< "Enter academic year: " << endl; // Se pide el año del curso académico
        getline(cin, idY); // Se introduce el año del curso académico con getline para evitar problemas con el buffer de teclado

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
            error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            salir = 1; // Se cambia el valor de la variable "salir"
        }
        if(idY.empty()){ // Si el año del curso académico está vacío, se muestra un mensaje de error
            error(ERR_EMPTY); // Se muestra un mensaje de error
            seIntrodujo = -1; // Se cambia el valor de la variable "seIntrodujo"
        }
        
        if(largo > 0 && seIntrodujo == 1){ // Si el vector no está vacío y se ha introducido un valor
            idYInt = stoi(idY); // Se convierte el año del curso académico a entero

            for(recorredor = 0; recorredor < largo && salir == 0; recorredor++){ // Se recorre el vector para comprobar si existe el curso académico
                if(listYears[recorredor].id == idYInt){ // Si existe el curso académico, se añade el profesor
                    do{ // Bucle para introducir el nombre del profesor
                        cout << "Enter teacher name: " << endl; // Se pide el nombre del profesor
                        getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado
                        cin.get(); // Se limpia el buffer de teclado

                        if(profesor.name.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
                            error(ERR_EMPTY); // Se muestra un mensaje de error
                            salir = 1; // Se cambia el valor de la variable "salir"
                        }

                        for(recorredor2 = 0; 
                        (recorredor2 < listYears[recorredor].listTeachers.size()||listYears[recorredor].listTeachers.size() == 0) && salir == 0; 
                        recorredor2++){ // Se recorre el vector para comprobar si ya existe el profesor

                            if(listYears[recorredor].listTeachers[recorredor2].name == nombre){ // Si ya existe el profesor, se muestra un mensaje de error
                                error(ERR_DUPLICATED); // Se muestra un mensaje de error
                            }
                            else{ // Si no existe el profesor, se añade
                                cout << "Enter teacher nickname: " << endl; // Se pide el apodo del profesor
                                getline(cin, apodo); // Se introduce el apodo del profesor con getline para evitar problemas con el buffer de teclado
                                cin.get(); // Se limpia el buffer de teclado

                                cout << "Enter subject: " << endl; // Se pide la asignatura del profesor                          
                                getline(cin, asignatura); // Se introduce la asignatura del profesor con getline para evitar problemas con el buffer de teclado
                                cin.get(); // Se limpia el buffer de teclado

                                if(asignatura.size() > 49){ // Si la asignatura del profesor es mayor a 49 caracteres, se acorta
                                    asignatura = asignatura.substr(0, 48); // Se acorta la asignatura del profesor hasta 49 caracteres
                                } 
                                else if(asignatura.empty()){ // Si la asignatura del profesor está vacía, se muestra un mensaje de error
                                    error(ERR_EMPTY); // Se muestra un mensaje de error
                                    salir = 1; // Se cambia el valor de la variable "salir"
                                }

                                if (asignatura.size() <= 49 && !asignatura.empty()) { // Si la asignatura del profesor no está vacía y no supera los 49 caracteres
                                    do { // Bucle para introducir la puntuación del profesor
                                        cout << "Enter rating: " << endl; // Se pide la puntuación del profesor
                                        cin >> puntuacion; // Se introduce la puntuación del profesor
                                        cin.get(); // Se limpia el buffer de teclado

                                        puntuacionFl = stof(puntuacion); // Se convierte la puntuación del profesor a float
                                    
                                        if (puntuacion.empty()) { // Si la puntuación del profesor está vacía, se muestra un mensaje de error   
                                            puntuacionFl = 0; // Se cambia el valor de la variable "puntuacionFl"
                                            salir = 1; // Se cambia el valor de la variable "salir"
                                        }
                                        else if(puntuacionFl < 0 || puntuacionFl >= 5) { // Si la puntuación del profesor no está entre 0 y 5, se muestra un mensaje de error
                                            error(ERR_RATING); // Se muestra un mensaje de error
                                            puntuacionFl = -1; // Se cambia el valor de la variable "puntuacionFl"
                                        }
                                        else if(puntuacionFl >= 0 && puntuacionFl < 5){ // Si la puntuación del profesor está entre 0 y 5, se añade el profesor
                                            profesor.name = nombre; // Se añade el nombre del profesor al registro
                                            profesor.nickname = apodo; // Se añade el apodo del profesor al registro
                                            for(int recorredor3 = 0; recorredor3 < asignatura.size(); recorredor3++){ // Se recorre la asignatura del profesor
                                                profesor.subject[recorredor3] = asignatura[recorredor3]; // Se añade la asignatura del profesor al registro
                                            }
                                            profesor.rating = puntuacionFl; // Se añade la puntuación en float del profesor al registro
                                            listYears[recorredor].listTeachers.push_back(profesor); // Se añade el profesor al vector

                                            cout<< endl << "Teacher added" << endl << endl; // Se muestra un mensaje de éxito

                                            salir = 2; // Se cambia el valor de la variable "salir"
                                        }
                                    } while (puntuacionFl < 0 || puntuacionFl >= 5); 
                                }
                           }
                        }
                    } while (salir == 0);
                }
            }
        }
    } while (salir == 0 && seIntrodujo == 1); 
}



//FUNCION PARA BORRAR UN PROFESOR
void deleteTeacher(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        seIntrodujo = 1, // Variable para saber si se ha introducido un valor
        salir = 0, // Variable para salir del bucle. Salir 1 para salir por error, salir 2 para salir por éxito
        recorredor, // Variable para recorrer el vector
        recorredor2; // Variable para recorrer el vector
    float puntuacion; // Variable para la puntuación del profesor
    string nombre; // Variable para el nombre del profesor
    
    do{ // Bucle para introducir el nombre del profesor
        cout << "Enter teacher name: " << endl; // Se pide el nombre del profesor
        getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado
        cin.get(); // Se limpia el buffer de teclado

        if(nombre.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
            error(ERR_EMPTY); // Se muestra un mensaje de error
            seIntrodujo = -1; // Se cambia el valor de la variable "seIntrodujo"
            salir = 1; // Se cambia el valor de la variable "salir"
        }

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
            error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            salir = 1; // Se cambia el valor de la variable "salir"
        } else{ // Si el vector no está vacío y se ha introducido un valor
            for(recorredor = 0; recorredor < largo && salir == 0; recorredor++){ // Se recorre el vector para comprobar si existe el profesor
                for(recorredor2 = 0; recorredor2 < listYears[recorredor].listTeachers.size() && salir == 0; recorredor2++){ // Se recorre el vector para comprobar si existe el profesor
                    if(listYears[recorredor].listTeachers[recorredor2].name == nombre){ // Si existe el profesor, se elimina
                        listYears[recorredor].listTeachers.erase(listYears[recorredor].listTeachers.begin() + recorredor2); // Se elimina el profesor del vector
                        salir = 2; // Se cambia el valor de la variable "salir"
                    }
                }
            }
            if(salir == 0){ // Si no existe el profesor, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            } 
            else if(salir == 2){ // Si se ha eliminado el profesor, se muestra un mensaje de éxito
                cout << endl << "Teacher deleted" << endl << endl; // Se muestra un mensaje de éxito
            }
        }
    } while(salir == 0 && seIntrodujo == 1); // Mientras no se haya eliminado el profesor y se haya introducido un valor
}
