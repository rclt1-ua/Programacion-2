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
void showTeacher(const vector<AcademicYear> &listYears);
void addPhrase(vector<AcademicYear> &listYears);
void summary(vector<AcademicYear> &listYears);
void SiProfesorExiste(vector<AcademicYear> &listYears, const int idYInt);
void Ordenar(vector<AcademicYear>& listYears);


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
            case 'q': // Salir del programa si se introduce la opción 'q'
                break;
            default: 
                error(ERR_OPTION);
        }
    }while(option!='q');
}

//FUNCION PARA AÑADIR UN CURSO ACADEMICO
void addAcademicYear(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        recorredor, // Variable para recorrer el vector
        idYInt; // Variable para el año del curso académico en entero
    bool encontrado; // Variable para saber si se ha encontrado el curso académico
    string idY; // Variable para el año del curso académico en string
    AcademicYear anyo; // Variable para el curso académico
    
    do{ 
        encontrado = false;
        cout<< "Enter academic year:";
            getline(cin, idY); // Se introduce el año del curso académico con getline para evitar problemas con el buffer de teclado

        if(idY.empty()){ // Si el año del curso académico está vacío, se muestra un mensaje de error
                error(ERR_EMPTY); // Se muestra un mensaje de error
            return; // Se sale de la función
        }

        if(largo == 0){ // Si el vector está vacío, se añade el curso académico
                idYInt = stoi(idY); // Se convierte el año del curso académico a entero
                anyo.id = idYInt; // Se añade el año del curso académico al registro
            listYears.push_back(anyo); // Se añade el curso académico al vector
            return; // Se sale del modulo por fallo
        }
        else if(largo > 0 && !idY.empty()){ // Si el año del curso académico no está vacío, se comprueba si ya existe
                idYInt = stoi(idY); // Se convierte el año del curso académico a entero

            for(recorredor = 0; recorredor < largo && !encontrado; recorredor++){ // Se recorre el vector para comprobar si ya existe el curso académico
                if(listYears[recorredor].id == idYInt){ // Si ya existe el curso académico, se cambia el valor de la variable "encontrado"
                    encontrado = true; // Se cambia el valor de la variable encontrado
                }
            }

            if(encontrado){ // Si ya existe el curso académico, se muestra un mensaje de error
                error(ERR_DUPLICATED); // Se muestra un mensaje de error
            }
            else{ 
                    anyo.id = idYInt; // Se añade el año del curso académico al registro
                listYears.push_back(anyo); // Se añade el curso académico al vector
                return; // Se sale del modulo
            }  
        }
    } while(encontrado); // Mientras ya exista el curso académico
}

//FUNCION PARA ELIMINAR UN CURSO ACADEMICO
void deleteAcademicYear(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        recorredor, // Variable para recorrer el vector
        idYInt; // Variable para el año del curso académico en entero
    bool eliminado, // Variable para saber si se ha eliminado el curso académico
        seIntrodujo; // Variable para saber si se ha introducido un valor
    string idY; // Variable para el año del curso académico en string

    do{ 
        eliminado = false;
        seIntrodujo = true;

        cout<< "Enter academic year: ";
            cin >> idY;
                cin.get();

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            return; // Se sale de la función
        }

        if(idY.empty()){ // Si el año del curso académico pedido está vacío, se muestra un mensaje de error
                error(ERR_EMPTY); // Se muestra un mensaje de error
                seIntrodujo = false; // Se cambia el valor de la variable "seIntrodujo"  
        }    
        else{ // Si el año del curso académico pedido no está vacío, se comprueba si existe
                idYInt = stoi(idY); // Se convierte el año del curso académico a entero
            for(recorredor = 0; recorredor < largo && !eliminado; recorredor++){ // Se recorre el vector para comprobar si existe el curso académico
                if(listYears[recorredor].id == idYInt){ // Si existe el curso académico, se elimina
                    listYears.erase(listYears.begin() + recorredor); // Se elimina el curso académico del vector
                        eliminado = true; // Se cambia el valor de la variable eliminado
                }
            }
            
            if(!eliminado){ // Si no existe el curso académico y no se elimina, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            }
        }  
    } 
    while(!eliminado && seIntrodujo); // Mientras no se haya eliminado el curso académico y se haya introducido un valor
}


//FUNCION PARA AÑADIR UN PROFESOR
void addTeacher(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        idYInt, // Variable para el año del curso académico en entero
        recorredor, // Variable para recorrer el vector. Recorredor para el vector de años
        puntuacionInt; // Variable para la puntuación del profesor
    size_t recorredor2, // Variable para recorrer el vector de profesores
        recorredor3; // Variable para recorrer el vector de asignatura y asignarla a la variable subject
    bool seIntrodujo, // Variable para saber si se ha introducido un valor
        salir, // Variable para salir del bucle
        duplicado = false; // Variable para verificar si el profesor ya existe
    string nombre, asignatura, apodo, idY, puntuacion; // Variables para el nombre, asignatura, apodo, año del curso académico y puntuación del profesor
    Teacher profesor; // Variable para el profesor
    
    do{ // Bucle para introducir el año del curso académico
        seIntrodujo = true;
        salir = false;

        cout<< "Enter academic year: "; // Se pide el año del curso académico
            getline(cin, idY); // Se introduce el año del curso académico con getline para evitar problemas con el buffer de teclado

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
               error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            return; // Se cambia el valor de la variable salir
        }
        if(idY.empty()){ // Si el año del curso académico está vacío, se muestra un mensaje de error
                error(ERR_EMPTY); // Se muestra un mensaje de error
                seIntrodujo = false; // Se cambia el valor de la variable seIntrodujo
        }
        
        if(largo > 0 && seIntrodujo){ // Si el vector no está vacío y se ha introducido un valor
            idYInt = stoi(idY); // Se convierte el año del curso académico a entero

            SiProfesorExiste(listYears, idYInt); // Se llama a la función para realizar los procesos de añadir el profesor
        }
    } while (!salir && seIntrodujo);  // Mientras no se haya añadido el profesor y se haya introducido un valor
}





//FUNCION PARA BORRAR UN PROFESOR
void deleteTeacher(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        recorredor; // Variable para recorrer el vector
    size_t recorredor2; // Variable para recorrer el vector de profesores
    bool seIntrodujo, // Variable para saber si se ha introducido un valor
        salir; // Variable para salir del bucle. 
    string nombre; // Variable para el nombre del profesor
    
    do{ // Bucle para introducir el nombre del profesor
        seIntrodujo = true;
        salir = false;

        cout << "Enter teacher name: "; // Se pide el nombre del profesor
            getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado

        if(nombre.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
                error(ERR_EMPTY); // Se muestra un mensaje de error            
                seIntrodujo = false; // Se cambia el valor de la variable seIntrodujo
                salir = true; // Se cambia el valor de la variable salir
            return; // Se sale de la función
        }

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
                salir = true; // Se cambia el valor de la variable salir
        } else{ // Si el vector no está vacío y se ha introducido un valor
            for(recorredor = 0; recorredor < largo && !salir; recorredor++){ // Se recorre el vector para comprobar si existe el profesor
                for(recorredor2 = 0; recorredor2 <= listYears[recorredor].listTeachers.size() && !salir; recorredor2++){ // Se recorre el vector para comprobar si existe el profesor
                    if(listYears[recorredor].listTeachers[recorredor2].name == nombre){ // Si existe el profesor, se elimina
                        listYears[recorredor].listTeachers.erase(listYears[recorredor].listTeachers.begin() + recorredor2); // Se elimina el profesor del vector
                        salir = true; // Se cambia el valor de la variable salir
                    }
                }
            }
            if(!salir){ // Si no existe el profesor, se muestra un mensaje de error
                error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            } 
        }
    } while(!salir && seIntrodujo); // Mientras no se haya eliminado el profesor y se haya introducido un valor
}


//FUNCION PARA MOSTRAR TODOS LOS DATOS DE UN PROFESOR
void showTeacher(const vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        recorredor1, // Variable para el año del curso académico en entero y para recorrer el vector
        recorredor3; // Variable para recorrer el vector de frases
    size_t recorredor2;
    bool seIntrodujo, // Variable para saber si se ha introducido un valor
        mostrado; // Variable para salir del bucle.
    string nombre, // Variable para el nombre del profesor
        subject; // Variable para la asignatura del profesor

    do{ // Mientras no se haya introducido un valor
        mostrado = false; // Se cambia el valor de la variable eliminado
        seIntrodujo = true; // Se cambia el valor de la variable seIntrodujo

        cout << "Enter teacher name: "; // Se pide el nombre del profesor
            getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado

        if(nombre.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
                error(ERR_EMPTY); // Se muestra un mensaje de error
                seIntrodujo = false; // Se cambia el valor de la variable seIntrodujo
            return;
        }

        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error
            error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            mostrado = false;
        } 
        else{ // Si el vector no está vacío y se ha introducido un valor
            for(recorredor1 = 0; recorredor1 < largo && !mostrado; recorredor1++){ // Se recorre el vector para comprobar si existe el profesor
                for(recorredor2 = 0; recorredor2 < listYears[recorredor1].listTeachers.size() && !mostrado; recorredor2++){ // Se recorre el vector para comprobar si existe el profesor
                    if(listYears[recorredor1].listTeachers[recorredor2].name == nombre){ // Si existe el profesor, se elimina
                        cout << "Academic year: " << listYears[recorredor1].id << endl; // Se muestra el año académico
                        cout << "Name: " << listYears[recorredor1].listTeachers[recorredor2].name << endl; // Se muestra el nombre del profesor
                        
                        if(listYears[recorredor1].listTeachers[recorredor2].nickname != ""){// Si el apodo del profesor no está vacío, se muestra
                            cout << "Nickname: " << listYears[recorredor1].listTeachers[recorredor2].nickname << endl; // Se muestra el apodo del profesor
                        }

                        subject = listYears[recorredor1].listTeachers[recorredor2].subject; // Se añade la asignatura del profesor a la variable subject
                            cout << "Subject: " << subject << endl; // Se muestra la asignatura del profesor

                        if(listYears[recorredor1].listTeachers[recorredor2].rating != 0){ // Si el rating del profesor no es 0, se muestra
                            cout << "Rating: " ;
                            for(recorredor3 = 0; recorredor3 < listYears[recorredor1].listTeachers[recorredor2].rating; recorredor3++){ // Se muestra el rating del profesor
                                cout << "*";
                            }
                            cout << endl;
                        }
                    
                            cout << endl;
                        if(listYears[recorredor1].listTeachers[recorredor2].listPhrases.size() > 0){ // Si el vector de frases del profesor no está vacío, se muestra
                            for (size_t recorredor3U = 0; recorredor3U < listYears[recorredor1].listTeachers[recorredor2].listPhrases.size(); recorredor3U++) { // Se recorre el vector para mostrar las frases del profesor
                                cout << "Phrase " << recorredor3U + 1; // Se muestra el número de frase

                                if (listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].date.day != 0) { // Si la fecha no es igual a cero, se muestra
                                    cout << " (" << listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].date.year  // Se muestra la fecha de la frase
                                    << "-" << listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].date.month // Se muestra la fecha de la frase
                                    << "-" << listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].date.day << ") "; // Se muestra la fecha de la frase
                                } 
                                else{ // Si la fecha está vacía, se muestra un espacio
                                    cout << " "; // Se muestra un espacio
                                }

                                if(listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].rating != 0){ // Si el rating de la frase no es 0, se muestra
                                    cout << "[" 
                                    << listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].rating // Se muestra el rating de la frase
                                    << "]: "; 
                                }
                                else{ // Si el rating de la frase es 0, se muestra un espacio
                                    cout << ": "; // Se muestra dos puntos y un espacio
                                }

                                cout << listYears[recorredor1].listTeachers[recorredor2].listPhrases[recorredor3U].text << endl; // Se muestra el texto de la frase
                                
                                mostrado = true; // Se cambia el valor de la variable mostrado
                            }
                        } 
                        else{
                            mostrado = true; // Se cambia el valor de la variable mostrado 
                        }
                        
                        if(mostrado){
                            return;
                        }
                    }
                }
            }

        }
    } while(!mostrado && seIntrodujo);
}

//FUNCION PARA BORRAR UN PROFESOR
void addPhrase(vector<AcademicYear> &listYears){
    int largo = listYears.size(), // Tamaño del vector
        recorredor, // Variable para recorrer el vector
        dia, mes, anyo, contador = 0, // Variables para el día, mes y año en int. COontador para saber si se ha introducido el guion
        puntFra; // Variable para la puntuación de la frase
    size_t recorredor2, recorredor3; // Variable para recorrer el vector de profesores y frases
    bool seIntrodujo, // Variable para saber si se ha introducido un valor
        salir; // Variable para salir del bucle. 
    string nombre, frasest, fecha, // Variable para el nombre del profesor y para la frase
        diaStr, mesStr, anyoStr, // Variables para el día, mes y año en string
        puntFraStr; // Variable para la puntuación de la frase en string
    Phrase frase; // Variable para la frase

    do{ // Bucle para introducir el nombre del profesor
        seIntrodujo = true;
        salir = false; 

        cout << "Enter teacher name: "; // Se pide el nombre del profesor
            getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado

        if(nombre.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
            error(ERR_EMPTY); // Se muestra un mensaje de error
                seIntrodujo = false; // Se cambia el valor de la variable SeIntrodujo
                salir = true; // Se cambia el valor de la variable salir
            return;
        }
 
        if(largo == 0){ // Si el vector está vacío, se muestra un mensaje de error       
            error(ERR_NOT_EXIST); // Se muestra un mensaje de error
            salir = true;
        } 
        else{ // Si el vector no está vacío y se ha introducido un valor
            for(recorredor = 0; recorredor < largo && !salir; recorredor++){ // Se recorre el vector para comprobar si existe el profesor
                for(recorredor2 = 0; recorredor2 < listYears[recorredor].listTeachers.size() && !salir; recorredor2++){ // Se recorre el vector para comprobar si existe el profesor
                    if(listYears[recorredor].listTeachers[recorredor2].name == nombre){ // Si existe el profesor, se elimina
                        cout << "Enter phrase: "; // Se pide la frase
                            getline(cin, frasest); // Se introduce la frase con getline para evitar problemas con el buffer de teclado

                        if(frasest.empty()){
                            error(ERR_EMPTY); // Se muestra un mensaje de error
                                seIntrodujo = false; // Se cambia el valor de la variable seIntrodujo
                                salir = true; // Se cambia el valor de la variable salir
                            return;
                        } 
                        else{
                            frase.text = frasest; // Se introduce la frase en el registro

                            cout << "Enter date (year-month-day):"; // Se pide la fecha
                            getline(cin, fecha); // Se introduce la fecha con getline para evitar problemas con el buffer de teclado

                            if(fecha.empty()){
                                frase.date.year = 0;
                                frase.date.month = 0;
                                frase.date.day = 0;
                            } 
                            else{
                                for(recorredor3 = 0; recorredor3 < fecha.size() && contador < 2; recorredor3++){
                                    if(fecha[recorredor3] == '-' && contador == 0){
                                        contador++;
                                        anyoStr = fecha.substr(0, recorredor3);
                                        anyo = stoi(anyoStr);
                                        frase.date.year = anyo;
                                    }
                                    else if(fecha[recorredor3] == '-' && contador == 1){
                                        contador++;
                                        mesStr = fecha.substr(anyoStr.size() + 1, recorredor3 - anyoStr.size() - 1);
                                        mes = stoi(mesStr);
                                        frase.date.month = mes;
                                        diaStr = fecha.substr(recorredor3 + 1, fecha.size() - recorredor3 - 1);
                                        dia = stoi(diaStr);
                                        frase.date.day = dia;
                                    } 
                                }
                            }

                            do{
                                cout << "Enter rating: "; // Se pide la puntuación
                                getline(cin, puntFraStr); // Se introduce la puntuación

                                if(puntFraStr.empty()){
                                    puntFra = 0;
                                }
                                else{
                                    puntFra = stoi(puntFraStr);
                                }

                                if(puntFra < 0 || puntFra > 10){
                                    error(ERR_RATING); // Se muestra un mensaje de error
                                }
                                else{
                                    frase.rating = puntFra; // Se introduce la puntuación en el registro
                                    listYears[recorredor].listTeachers[recorredor2].listPhrases.push_back(frase); // Se añade la frase al vector
                                        salir = true; // Se cambia el valor de la variable "salir"
                                }

                            } while(puntFra < 0 || puntFra > 10); // Mientras la puntuación no esté entre 0 y 10
                        }
                    }
                }
            }
        }
    } while(!salir && seIntrodujo); // Mientras no se haya añadido la frase y se haya introducido un valor
}

//FUNCION PARA MOSTRAR UN RESUMEN DE TODAS LAS FRASES DE TODOS LOS CURSOS
void summary(vector<AcademicYear> &listYears) {
    int largo = listYears.size(); // Tamaño del vector
    int recorredor; // Variable para recorrer el vector
    size_t recorredor2, // Variable para recorrer el vector de profesores
        recorredor3, // Variable para recorrer el vector de frases
        organizador1, organizador2; // Variable para recorrer el vector y ordenar
    string asignatura; // Variable para la asignatura del profesor
    bool anyoImpreso;
    AcademicYear auxiliar; // Variable para guardar el valor durante el intercambio

    if (largo == 0) { // Si el vector está vacío, se muestra un mensaje de error
        error(ERR_NOT_EXIST); // Se muestra un mensaje de error
        return;
    }

    Ordenar(listYears); // Se ordena el vector de años académicos (de mayor a menor

    for (recorredor = 0; recorredor < largo; recorredor++) { // Se recorre el vector para mostrar el resumen
        anyoImpreso = false;

        for (recorredor2 = 0; recorredor2 < listYears[recorredor].listTeachers.size(); recorredor2++) { // Se recorre el vector para mostrar el resumen
            if (listYears[recorredor].listTeachers[recorredor2].listPhrases.size() > 0) { // Si el vector de frases del profesor no está vacío, se muestra

                if (!anyoImpreso) {
                    cout << "Academic year: " << listYears[recorredor].id << endl; // Se muestra el año académico
                }

                for (recorredor3 = 0; recorredor3 < listYears[recorredor].listTeachers[recorredor2].listPhrases.size(); recorredor3++) { // Se recorre el vector para mostrar las frases del profesor
                    cout << listYears[recorredor].listTeachers[recorredor2].name; // Se muestra el nombre del profesor

                    if (listYears[recorredor].listTeachers[recorredor2].listPhrases[recorredor3].rating != 0) { // Si el rating de la frase no es 0, se muestra
                        cout << " - "
                            << listYears[recorredor].listTeachers[recorredor2].listPhrases[recorredor3].rating // Se muestra el rating de la frase
                            << " - ";
                    }
                    else { // Si el rating de la frase es 0, se muestra un espacio
                        cout << " - "; // Se muestra dos puntos y un espacio
                    }
                    cout << listYears[recorredor].listTeachers[recorredor2].listPhrases[recorredor3].text << endl; // Se muestra el texto de la frase
                }

                anyoImpreso = true;
            }
        }
    }
}











//FUNCION PARA ORDENAR LOS CURSOS ACADEMICOS
void Ordenar(vector<AcademicYear>& listYears) {
    int largo = listYears.size(), // Tamaño del vector
        recorredor, recorredor2; // Variable para recorrer el vector
    AcademicYear auxiliar;// Variable para guardar el valor durante el intercambio

    for (recorredor = 0; recorredor < largo - 1; recorredor++) { // Se recorre el vector para ordenar los cursos académicos
        for (recorredor2 = 0; recorredor2 < largo - recorredor - 1; recorredor2++) { // Se obtiene posiciones para ordenar
            if (listYears[recorredor2].id < listYears[recorredor2 + 1].id) { // Se compara el valor actual con el siguiente
                auxiliar = listYears[recorredor2]; // Se guarda el valor actual
                listYears[recorredor2] = listYears[recorredor2 + 1]; // Se intercambian los valores
                listYears[recorredor2 + 1] = auxiliar; // Se intercambian los valores
            }
        }
    }
}




//FUNCION PARA AÑADIR UN PROFESOR
void SiProfesorExiste(vector<AcademicYear> &listYears, const int idYInt){
    int largo = listYears.size(), // Tamaño del vector
        recorredor, // Variable para recorrer el vector. Recorredor para el vector de años
        recorredor2, // Variable para recorrer el vector de profesores
        recorredor3, // Variable para recorrer el vector de asignatura y asignarla a la variable subject
        puntuacionInt; // Variable para la puntuación del profesor
    bool salir = false, // Variable para salir del bucle
        duplicado = false; // Variable para verificar si el profesor ya existe
    Teacher profesor; // Variable para el profesor
    string nombre, asignatura, apodo, puntuacion; // Variables para el nombre, asignatura, apodo y puntuación del profesor

    for(recorredor = 0; recorredor < largo && !salir; recorredor++){ // Se recorre el vector para comprobar si existe el curso académico
        if(listYears[recorredor].id == idYInt){ // Si existe el curso académico, se añade el profesor
            do{ // Bucle para introducir el nombre del profesor
                cout << "Enter teacher name: "; // Se pide el nombre del profesor
                    getline(cin, nombre); // Se introduce el nombre del profesor con getline para evitar problemas con el buffer de teclado

               if(nombre.empty()){ // Si el nombre del profesor está vacío, se muestra un mensaje de error
                    error(ERR_EMPTY); // Se muestra un mensaje de error
                        salir = true; // Se cambia el valor de la variable salir
                    return;
                } 

                for (recorredor2 = 0; (recorredor2 <= listYears[recorredor].listTeachers.size() && !salir); recorredor2++) { // Se recorre el vector para comprobar si ya existe el profesor
                    if (recorredor2 < listYears[recorredor].listTeachers.size() && 
                            listYears[recorredor].listTeachers[recorredor2].name == nombre){ // Si ya existe el profesor, se muestra un mensaje de error
                            error(ERR_DUPLICATED); // Se muestra un mensaje de error
                            duplicado = true; // Se cambia el valor de la variable duplicado
                    }
                            
                    if(!duplicado){ // Si no existe el profesor, se añade
                        cout << "Enter nickname: "; // Se pide el apodo del profesor
                            getline(cin, apodo); // Se introduce el apodo del profesor con getline para evitar problemas con el buffer de teclado

                        cout << "Enter subject: "; // Se pide la asignatura del profesor                          
                            getline(cin, asignatura); // Se introduce la asignatura del profesor con getline para evitar problemas con el buffer de teclado

                        if(asignatura.empty()){ // Si la asignatura del profesor está vacía, se muestra un mensaje de error
                                error(ERR_EMPTY); // Se muestra un mensaje de error
                                salir = true; // Se cambia el valor de la variable salir
                            return;
                        }
                        else if(asignatura.size() > 49){ // Si la asignatura del profesor es mayor a 49 caracteres, se acorta
                            asignatura = asignatura.substr(0, 48); // Se acorta la asignatura del profesor hasta 49 caracteres
                        } 

                        if (asignatura.size() <= 49 && !asignatura.empty()) { // Si la asignatura del profesor no está vacía y no supera los 49 caracteres
                            do{
                                cout << "Enter rating: "; // Se pide la puntuación del profesor
                                    getline(cin, puntuacion); // Se introduce la puntuación del profesor con getline para evitar problemas con el buffer de teclado

                                puntuacionInt = stoi(puntuacion); // Se convierte la puntuación del profesor a int
                                        
                                if (puntuacion.empty()) { // Si la puntuación del profesor está vacía, se muestra un mensaje de error   
                                    puntuacionInt = 0; // Se cambia el valor de la variable puntuacionInt
                                }
                                else if(puntuacionInt < 0 || puntuacionInt > 5) { // Si la puntuación del profesor no está entre 0 y 5, se muestra un mensaje de error
                                    error(ERR_RATING); // Se muestra un mensaje de error
                                }
                                else if(puntuacionInt >= 0 && puntuacionInt <= 5){ // Si la puntuación del profesor está entre 0 y 5, se añade el profesor
                                                profesor.name = nombre; // Se añade el nombre del profesor al registro
                                                profesor.nickname = apodo; // Se añade el apodo del profesor al registro

                                        for (recorredor3 = 0; recorredor3 < asignatura.size(); recorredor3++) { // Se añade la asignatura del profesor al registro
                                            profesor.subject[recorredor3] = asignatura[recorredor3];
                                        }
                                        profesor.subject[recorredor3] = '\0'; // Se añade el carácter nulo al final de la asignatura del profesor

                                        profesor.rating = puntuacionInt; // Se añade la puntuación en int del profesor al registro
                                        listYears[recorredor].listTeachers.push_back(profesor); // Se añade el profesor al vector
                                    salir = true; // Se cambia el valor de la variable salir
                                }
                           } while (puntuacionInt < 0 || puntuacionInt > 5); // Mientras la puntuación del profesor no esté entre 0 y 5
                        }                           
                    }
                }
            } while (!salir); // Mientras no se haya añadido el profesor
        }
    }
}
