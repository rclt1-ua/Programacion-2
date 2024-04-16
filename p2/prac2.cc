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


// Declaración de modulos
void addQuestion(Database &data, int &numData);
void batchAddQuestions(Database &data, int &numData);
void deleteQuestion(Database &base);
void addTeacher(Database &data);
void addAnswers(Database &data);
void viewAnswers(Database &data);
void viewStatistics(Database &base);
void exportQuestions(Database &data);
void addBinTeachers(Database &data);
void loadTeachers(Database &data);
void comprobarNom(Database &data, string &nombre, bool &nombreCorrecto, bool &rn);
void validarFila(string &linea, int &tipoError, int &contador, bool &hayError);
void convertirCon(string &contrasenya);
void batchAddQuestionsComando(Database &data, int &numData, const char *fileRef);
void summary(int numLinea, int lineaError, int &numData, int &errorN);
void error(Error e);
void showMenu();

void pruebaS(Database data){
    int recorredor;

    for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){
        cout << data.questions[recorredor].id << ". (" << data.questions[recorredor].unit << ") " << data.questions[recorredor].question << endl;
    }
}

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
    int numData = 1,
        recorredor,
        recorredor2,
        contarF = 0,
        contarS = 0;
    data.nextId= numData;
    char option;
    string fileName;

    loadTeachers(data); // Cargamos los profesores de un fichero binario

    if(argc > 1){ // Comprobamos si hay argumentos
        for (recorredor2 = 1; recorredor2 < argc; recorredor2++) { // Recorremos los argumentos
            if (argv[recorredor2] != nullptr && strcmp(argv[recorredor2], "-s") == 0) { //  Comprobamos si hay un argumento '-s'
                contarS++;
            }
        }

        for (recorredor = 1; recorredor < argc ; recorredor++) {
            if (argv[recorredor] != nullptr && strcmp(argv[recorredor], "-f") == 0) { // Comprobamos si hay un argumento '-f'
                contarF++;
            }
        }
                
        if(contarF == 3){ // Comprobamos si hay 3 argumentos '-f'
            error(ERR_ARGS);
            return 0;
        }

        if(contarF == 2){
            for (recorredor = 1; recorredor < argc ; recorredor++) { // Recorremos los argumentos
                if (recorredor < argc && argv[recorredor + 1] != nullptr  && strcmp(argv[recorredor + 1], "-f") != 0) { // Comprobamos si no hay un argumento después de '-f'
                    error(ERR_ARGS); // Si no hay un argumento después de '-f', mostramos un error
                    return 0;
                }

                if (recorredor < argc&& argv[recorredor + 1] != nullptr && strcmp(argv[recorredor + 1], "-f") == 0) { // Comprobamos si hay un argumento después de '-f'
                    fileName = "-f"; // Asignamos el argumento después de '-f' a fileName
                }
            }
        }

        if(contarF == 1){ // Comprobamos si hay 1 argumento '-f'
            if(argc == 2){ // Comprobamos si hay 2 argumentos
                error(ERR_ARGS);// Si hay 2 argumentos, mostramos un error 
                return 0;
            }

            for (recorredor = 1; recorredor < argc ; recorredor++) { // Recorremos los argumentos
                if (argv[recorredor] != nullptr && strcmp(argv[recorredor], "-f") == 0){ // Comprobamos si hay un argumento '-f'
                    if(argv[recorredor + 1] != nullptr){// Comprobamos si hay un argumento después de '-f'
                        fileName = argv[recorredor + 1]; // Asignamos el argumento después de '-f' a fileName
                    }

                    if(argv[recorredor + 1] == nullptr){ // Comprobamos si no hay un argumento después de '-f'
                        error(ERR_ARGS); // Si no hay un argumento después de '-f', mostramos un error
                        return 0;
                    }
                }  
            }

        }

        for(recorredor = 1; recorredor < argc; recorredor++){ // Recorremos los argumentos
            if((contarF >=0 && contarF < 3) && (contarS >=0 && contarS < 2) && !fileName.empty()){ // Comprobamos si hay argumentos correctos

                if (argv[recorredor] != nullptr && strcmp(argv[recorredor], "-s") != 0 && 
                strcmp(argv[recorredor], "-f") != 0 && strcmp(argv[recorredor], fileName.c_str()) != 0){ // Comprobamos si hay argumentos correctos
                    error(ERR_ARGS); // Si hay argumentos incorrectos, mostramos un error
                    return 0;
                }  
            }
        }

        if(argc > 2){ // Comprobamos si hay más de 2 argumentos
            if(contarF == 0){ // Comprobamos si no hay argumentos '-f'
                error(ERR_ARGS); // Si no hay argumentos '-f', mostramos un error
                return 0;
            }
        }

        if(contarS == 2 && fileName != "-s"){ // Comprobamos si hay 2 argumentos '-s'
            error(ERR_ARGS); // Si hay 2 argumentos '-s', mostramos un error
            return 0;
        }

        if(contarF < 3 && contarF > 0){
            batchAddQuestionsComando(data, numData, fileName.c_str()); // Añadimos preguntas desde un fichero
        }

        if(contarS == 1 && fileName != "-s"){ // Comprobamos si hay un argumento '-s'
            viewStatistics(data); // Mostramos las estadísticas
            return 0;
        }
        else if(contarS == 2 && fileName == "-s"){ // Comprobamos si hay 2 argumentos '-s' y que fileName sea '-s'
            viewStatistics(data); // Mostramos las estadísticas
            return 0;
        }
        else{ // Si no hay argumentos '-s', mostramos el menú
            if(contarS > 1){ // Comprobamos si hay más de 1 argumento '-s' 
                error(ERR_ARGS);
                return 0;
            }
        }
    }


    for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){ // Recorremos las preguntas
        numData = data.questions[recorredor].id; // Asignamos el id a numData para obtener el siguiente id
    }


    do{
        showMenu();
        cin >> option;
        cin.get();
        
        switch(option){
            case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                addQuestion(data, numData);
                break;
            case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                batchAddQuestions(data, numData);
                break;
            case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
                deleteQuestion(data);
                break;
            case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
                addTeacher(data);
                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                addAnswers(data);
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                viewAnswers(data);
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                viewStatistics(data);
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                exportQuestions(data);
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

    addBinTeachers(data);


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

        cout << "Enter unit:"; // Pedimos la unidad
        getline(cin, unitStr);

        if (unitStr.empty()) { // Comprobamos si la unidad está vacía
            error(ERR_EMPTY);
            return; // Si está vacía, mostramos un error
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

            cout << "Enter question:"; // Pedimos la pregunta
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
            pregunta.id = data.nextId; // Asignamos el id a la pregunta
            pregunta.unit = numero; // Asignamos la unidad a la pregunta
            pregunta.question = preguntaStr; // Asignamos la pregunta a la pregunta
            data.questions.push_back(pregunta); // Añadimos la pregunta a la base de datos
            data.nextId++; // Aumentamos el id para la siguiente pregunta
        }
    }
}


void batchAddQuestions (Database &data, int &numData){
    string fileName, // Nombre del fichero
        linea; // Línea del fichero
    int numLinea = 0, // Número de línea
        tipoError = 0, // Tipo de error
        contador, // Contador de '|'
        lineaError = 0, // Línea con error
        preguntasAñadidas = 1, // Lineas sin error
        errorN; // Número de errores vacios
    bool equivocado, // Comprueba si el fichero está vacío
        hayError; // Comprueba si hay un error
    Question pregunta; 
    size_t pos1, pos2;

    do{
        equivocado = false;

        cout << "Enter filename: "; // Pedimos el nombre del fichero
        getline(cin, fileName);

        if(fileName.empty()){ // Comprobamos si el nombre del fichero está vacío
            error(ERR_EMPTY); // Si está vacío, mostramos un error
            return;
        }

        ifstream file(fileName); // Abrimos el fichero

        if (file.is_open()){ // Comprobamos si no se ha podido abrir el fichero
            errorN = 0;

            for(; getline(file, linea);){ // Leemos el fichero línea a línea
                numLinea++; // Aumentamos el número de línea
                
                validarFila(linea, tipoError, contador, hayError); // Validamos la línea

                if(tipoError == 1){
                  errorN++; // Si hay un error, disminuimos el número de línea
                }

                if(hayError && tipoError != 1){ // Si hay un error, mostramos el error
                    cout << "Error line " << numLinea << endl;// Mostramos el error
                    lineaError++; // Aumentamos el número de líneas con error
                }

                if(!hayError){ // Si no hay errores, añadimos la pregunta a la base de datos
                    if(contador == 2){ // Si hay dos '|'

                        pos1 = linea.find('|'); // Buscamos la primera posición del carácter '|'
                        pos2 = linea.find('|', pos1 + 1); // Buscamos la segunda posición del carácter '|'
        
                        pregunta.unit = stoi(linea.substr(0, pos1)); // Convertimos la unidad a entero
                        pregunta.question = linea.substr(pos1 + 1, pos2 - pos1 - 1); // Asignamos la pregunta
                        pregunta.answer = linea.substr(pos2 + 1); // Asignamos la respuesta
                        pregunta.id = data.nextId; // Asignamos el id a la pregunta

                        data.questions.push_back(pregunta); // Añadimos la pregunta a la base de datos
                        data.nextId++; // Aumentamos el id para la siguiente pregunta
                        preguntasAñadidas++; // Aumentamos el número de preguntas añadidas
                    }
                    else if(contador == 1){

                        pos1 = linea.find('|'); // Buscamos la primera posición del carácter '|'

                        pregunta.unit = stoi(linea.substr(0, pos1)); // Convertimos la unidad a entero
                        pregunta.question = linea.substr(pos1 + 1); // Asignamos la pregunta
                        pregunta.answer = ""; // Asignamos la respuesta vacía
                        pregunta.id = data.nextId; // Asignamos el id a la pregunta

                        data.questions.push_back(pregunta); // Añadimos la pregunta a la base de datos
                        data.nextId++; // Aumentamos el id para la siguiente pregunta
                        preguntasAñadidas++; // Aumentamos el número de preguntas añadidas
                    }
                }
            }

            summary(numLinea, lineaError, numData, errorN); // Mostramos el resumen de las preguntas añadidas

            file.close(); // Cerramos el fichero
        }
        else{
            error(ERR_FILE); // Mostramos el error ERR_FILE
            equivocado = true; // Si no se ha podido abrir el fichero, volvemos a pedir el nombre del fichero
        }
    }
    while(equivocado); // Si no se ha podido abrir el fichero, volvemos a pedir el nombre del fichero
}


void deleteQuestion(Database &base){
    string id;
    int idInt,
        recorredor;
    bool equivocado;

    do{
        equivocado = false;

        cout << "Enter question id: "; // Pedimos el id de la pregunta a eliminar
        getline(cin, id); // Leemos el id de la pregunta a eliminar

        if(id.empty()){ // Comprobamos si el id está vacío
            error(ERR_EMPTY);   
            return;
        }

        try{
            idInt = stoi(id); // Convertimos el id a entero
        }
        catch(const std::invalid_argument&){ // Si no se puede convertir a entero, mostramos un error
            error(ERR_ID);
            equivocado = true;
        }

        if(!equivocado){ // Si se ha podido convertir a entero, buscamos la pregunta con ese id
            for(recorredor = 0; recorredor < (int)base.questions.size(); recorredor++){ // Recorremos las preguntas
                if((int)base.questions[recorredor].id == idInt){
                    base.questions.erase(base.questions.begin() + recorredor); // Eliminamos la pregunta
                    return;
                }
            }
            error(ERR_ID);
            equivocado = true; // Si no se ha encontrado la pregunta, mostramos un error
        }
    }
    while(equivocado); // Si no se ha encontrado la pregunta, volvemos a pedir el id
}


void addTeacher(Database &data){
    Teacher profesor;
    string nombre,
        contrasenya;
    int recorredor,
        errorContra;
    bool nombreCorrecto,
        passwordCorrecto,
        returnBool = false;

    comprobarNom(data, nombre, nombreCorrecto, returnBool); // Comprobamos el nombre del profesor

    if(returnBool){ // Si el nombre está vacío, salimos de la función
        return;
    }

    if(nombreCorrecto){ // Si el nombre es correcto, comprobamos la contraseña
        do{
            passwordCorrecto = false; 
            errorContra = 0;

            cout << "Enter password:"; // Pedimos la contraseña
            getline(cin, contrasenya);

            if (contrasenya.empty()) { // Comprobamos si la contraseña está vacía
                error(ERR_EMPTY);
                return;
            }

            for(recorredor = 0; recorredor < (int)contrasenya.size() && errorContra == 0; recorredor++){ // Comprobamos si la contraseña contiene caracteres válidos
                if(isdigit(contrasenya[recorredor])){ // Comprobamos si la contraseña contiene solo dígitos
                    passwordCorrecto = true;
                }
                else{ // Si la contraseña no contiene solo dígitos, mostramos un error
                    error(ERR_PASSWORD);
                    errorContra++;
                }
            }

            if(passwordCorrecto){ // Si la contraseña contiene dígitos, comprobamos si tiene 4 dígitos
                if(contrasenya.size() != 4){ 
                    error(ERR_PASSWORD);
                    passwordCorrecto = false; // Si la contraseña no tiene 4 dígitos, mostramos un error
                }
            }

        } while (!passwordCorrecto); // Si la contraseña no es correcta, volvemos a pedirla

        if(passwordCorrecto){
            convertirCon(contrasenya); // Convertimos la contraseña

            strcpy(profesor.name, nombre.c_str()); // Asignamos el nombre del profesor
            strcpy(profesor.password, contrasenya.c_str()); // Asignamos la contraseña del profesor
            profesor.answered = 0; // Inicializamos el número de respuestas a 0
            data.teachers.push_back(profesor); // Añadimos el profesor a la base de datos
        }
    }
}


void addAnswers(Database &data){
    int recorredor,
        posEncontrada,
        noContestadas,
        id,
        idRespondido;
    bool encontrado,
        correcto,
        idCorrecto,
        idConvertido,
        respuestaCorrecta;
    string nombre,
        contrasenya,
        idStr,
        respuesta;
    
    do{
        encontrado = false; // Inicializamos la variable a false

        cout << "Enter teacher name: "; // Pedimos el nombre del profesor
        getline(cin, nombre);

        if(nombre.empty()){ // Comprobamos si el nombre está vacío
            error(ERR_EMPTY);
            return;
        }

        if(!nombre.empty()){ // Si el nombre no está vacío, comprobamos si el profesor existe
            if(data.teachers.size() != 0){ // Comprobamos si hay profesores en la base de datos
                for(recorredor = 0; recorredor < (int)data.teachers.size() && !encontrado; recorredor++){ // Recorremos los profesores
                    if(nombre == data.teachers[recorredor].name){ // Comprobamos si el nombre del profesor es correcto
                        encontrado = true; // Si el nombre del profesor es correcto, asignamos la posición del profesor 
                        posEncontrada = recorredor; // Asignamos la posición del profesor
                    }
                }
            }
        }

        if(!encontrado){ // Si el profesor no existe, mostramos un error
            error(ERR_NAME); 
        }
    }
    while(!encontrado); // Si el profesor no existe, volvemos a pedir el nombre del profesor

    if(encontrado){ // Si el profesor existe, comprobamos la contraseña
        do{ 
            correcto = false;
            
            cout << "Enter password: "; // Pedimos la contraseña
            getline(cin, contrasenya);

            if(contrasenya.empty()){ // Comprobamos si la contraseña está vacía
                error(ERR_EMPTY);
                return; // Si la contraseña está vacía, mostramos un error y salimos de la función
            }

            convertirCon(contrasenya); // Convertimos la contraseña

            if(contrasenya == data.teachers[posEncontrada].password){
                correcto = true; // Si la contraseña es correcta, asignamos la variable a true
            }
            else{
                error(ERR_PASSWORD); // Si la contraseña no es correcta, mostramos un error
            }
        }
        while(!correcto); // Si la contraseña no es correcta, volvemos a pedirla
    }


    do{
        if(correcto){ // Si la contraseña es correcta, mostramos las preguntas sin responder
            noContestadas = 0;

            for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){ // Recorremos las preguntas
                if(data.questions[recorredor].answer.empty()){
                    cout << data.questions[recorredor].id << ". (" << data.questions[recorredor].unit << ") " << data.questions[recorredor].question << endl;
                    noContestadas++; // Aumentamos el número de preguntas sin responder
                }
            }

            if(noContestadas == 0){ // Comprobamos si no hay preguntas sin responder
                error(ERR_NO_QUESTIONS);
                return; // Si no hay preguntas sin responder, mostramos un error y salimos de la función
            }

            if(noContestadas > 0){ // Si hay preguntas sin responder, pedimos el id de la pregunta a responder
                do{
                    idCorrecto = false;
                    idConvertido = false;

                    cout << "Enter question id: "; // Pedimos el id de la pregunta a responder
                    getline(cin, idStr);

                    if(idStr.empty()){ // Comprobamos si el id está vacío
                        error(ERR_EMPTY);
                        return;
                    }

                    if(idStr == "b"){ // Comprobamos si el id es 'b'
                        return;
                    }

                    if(idStr != "b"){ // Si el id no es 'b', comprobamos si es correcto
                        try{ // Convertimos el id a entero
                            id = stoi(idStr);
                            idConvertido = true;
                        }
                        catch(const std::invalid_argument&){ // Si no se puede convertir a entero, mostramos un error
                            error(ERR_ID);
                        }
                    }

                    if(idConvertido){ // Si se ha podido convertir a entero, comprobamos si el id es correcto
                        for(recorredor = 0; recorredor < (int)data.questions.size() && !idCorrecto; recorredor++){ // Recorremos las preguntas
                                if(data.questions[recorredor].answer.empty() && (int)data.questions[recorredor].id == id){ // Comprobamos si la pregunta no tiene respuesta y si el id es correcto
                                    idCorrecto = true; // Si el id es correcto, asignamos la variable a true
                                    idRespondido = recorredor; // Asignamos la posición de la pregunta
                                }
                        }

                        if(!idCorrecto){
                                error(ERR_ID); // Si el id no es correcto, mostramos un error   
                        }
                    }
                } 
                while(!idCorrecto); // Si el id no es correcto, volvemos a pedir el id

                if(idCorrecto){ // Si el id es correcto, pedimos la respuesta
                    do{
                        respuestaCorrecta = true; 

                        cout << "Enter answer: "; // Pedimos la respuesta
                        getline(cin, respuesta);

                        if(respuesta.empty()){ // Comprobamos si la respuesta está vacía
                            error(ERR_EMPTY);
                            return;
                        }

                        if (respuesta.find('|') != string::npos) { // Comprobamos si la respuesta contiene el carácter '|'
                            error(ERR_CHAR);
                            respuestaCorrecta = false;
                        }
                    }
                    while(!respuestaCorrecta); // Si la respuesta no es correcta, volvemos a pedirla

                    if(respuestaCorrecta){ // Si la respuesta es correcta, asignamos la respuesta a la pregunta
                        data.questions[idRespondido].answer = respuesta; 
                        data.teachers[posEncontrada].answered++;
                    }
                }
            }
        }
    }
    while(idStr != "b"); // Si el id es 'b', salimos de la función. Mientras no sea 'b', seguimos pidiendo el id y mostrando las preguntas sin responder
}


void viewAnswers(Database &data){
    int recorredor;




    for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){ // Recorremos las preguntas
        if(!data.questions[recorredor].answer.empty()){ // Comprobamos si la pregunta tiene respuesta
            cout << data.questions[recorredor].id << ". (" 
            << data.questions[recorredor].unit << ") " 
            << data.questions[recorredor].question << ": "
            << data.questions[recorredor].answer << endl;
        }
    }

}


void viewStatistics(Database &base){
    int recorredor,\
        contadorPreguntas = 0,
        contadorRespuestas = 0;

    if(base.questions.size() != 0){ // Comprobamos si hay preguntas en la base de datos
        for(recorredor = 0; recorredor < (int)base.questions.size(); recorredor++){ // Recorremos las preguntas
            contadorPreguntas++; // Aumentamos el número de preguntas

            if(!base.questions[recorredor].answer.empty()){ // Comprobamos si la pregunta tiene respuesta
                contadorRespuestas++; // Aumentamos el número de respuestas
            }
        }
    }
    else{
        cout << "Total number of questions: 0" << endl;// Si no hay preguntas, el número de preguntas es 0
        cout << "Number of questions answered: 0" << endl;  // Si no hay preguntas, el número de respuestas es 0

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){ // Recorremos los profesores
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl; // Mostramos el nombre del profesor y el número de respuestas
        }
    }

    if(contadorRespuestas != 0 && contadorPreguntas != 0){ // Comprobamos si hay preguntas y respuestas
        cout << "Total number of questions: " << contadorPreguntas << endl; // Mostramos el número de preguntas
        cout << "Number of questions answered: " << contadorRespuestas << endl; // Mostramos el número de respuestas

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){ // Recorremos los profesores
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl; // Mostramos el nombre del profesor y el número de respuestas
        }
    }
    else if(contadorRespuestas == 0 && contadorPreguntas != 0){ // Comprobamos si hay preguntas y no hay respuestas
        cout << "Total number of questions: " << contadorPreguntas << endl; // Mostramos el número de preguntas
        cout << "Number of questions answered: 0" << endl; // Si no hay respuestas, el número de respuestas es 0

        for(recorredor = 0; recorredor < (int)base.teachers.size(); recorredor++){ // Recorremos los profesores
            cout << base.teachers[recorredor].name << ": " << base.teachers[recorredor].answered << endl; // Mostramos el nombre del profesor y el número de respuestas
        }
    }
}


void exportQuestions(Database &data){
    string filename;
    bool noAbierto;
    int recorredor;
    
    do{
        noAbierto = false;

        cout << "Enter filename: "; // Pedimos el nombre del fichero
        getline(cin, filename);
    
        if(filename.empty()){ // Comprobamos si el nombre del fichero está vacío
            error(ERR_EMPTY);
            return;
        }

        ofstream file(filename); // Abrimos el fichero

        if(file){ // Comprobamos si se ha podido abrir el fichero
            for(recorredor = 0; recorredor < (int)data.questions.size(); recorredor++){ // Recorremos las preguntas
                if(data.questions[recorredor].answer.empty()){ // Comprobamos si la pregunta no tiene respuesta
                    file << data.questions[recorredor].unit << "|" << data.questions[recorredor].question << endl; // Si la pregunta no tiene respuesta, guardamos la pregunta
                }
                else{ // Si la pregunta tiene respuesta, guardamos la pregunta y la respuesta
                    file << data.questions[recorredor].unit << "|" << data.questions[recorredor].question << "|" << data.questions[recorredor].answer << endl; // Guardamos la pregunta y la respuesta
                }
            }
            file.close(); // Cerramos el fichero
        }
        else{ // Si no se ha podido abrir el fichero, mostramos un error
            error(ERR_FILE);
            noAbierto = true;
        }
    }
    while(noAbierto);// Si no se ha podido abrir el fichero, volvemos a pedir el nombre del fichero
}


// Funciones auxiliares

void summary(int numLinea, int lineaError, int &numData, int &errorN){ // Función que muestra el resumen de las preguntas añadidas, sirve en el modulo batchAddQuestions    
    if(numLinea == 0){ // Comprobamos si el fichero está vacío
        cout << "Summary: 0/0 questions added" << endl;
    }
    else{
        cout << "Summary: " << numLinea - lineaError - errorN << "/" << numLinea - errorN << " questions added" << endl;
    }
} 

  
void addBinTeachers(Database &data){ // Función que guarda los profesores en un fichero binario
    ofstream file("teachers.bin", ios::binary); // Abrimos el fichero
    if (file.is_open()) { // Comprobamos si se ha podido abrir el fichero
        for (const auto& teacher : data.teachers) { // Recorremos los profesores
            file.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher)); // Guardamos los profesores en el fichero
        }
        file.close(); // Close the file
    }

}


void loadTeachers(Database &data){ // Función que carga los profesores de un fichero binario
    ifstream file;
    Teacher teacher;

    file.open("teachers.bin", ios::binary); // Abrimos el fichero
    if(file.is_open()){ // Comprobamos si se ha podido abrir el fichero
        while(file.read((char*)&teacher, sizeof(Teacher))){ // Leemos los profesores del fichero
            data.teachers.push_back(teacher); // Añadimos los profesores a la base de datos
        }
        file.close();// Cerramos el fichero
    }
}


void comprobarNom(Database &data, string &nombre, bool &nombreCorrecto, bool &rn){ // Función que comprueba el nombre del profesor. Se utiliza en la función addTeacher
    int recorredor,
        errorCarac;

    do{ // Pedimos el nombre del profesor hasta que sea correcto
        nombreCorrecto = false;
        rn = false;
        errorCarac = 0;

        cout << "Enter teacher name:"; // Pedimos el nombre del profesor
        getline(cin, nombre);
        
        if(nombre.empty()){ // Comprobamos si el nombre está vacío
            error(ERR_EMPTY);
            rn = true; //
            return;
        }

        for(recorredor = 0; recorredor < (int)nombre.size() && errorCarac == 0; recorredor++){ // Comprobamos si el nombre contiene caracteres válidos
            if(isalpha(nombre[recorredor]) || nombre[recorredor] == ' '){ // Comprobamos si el nombre contiene solo letras y espacios
                nombreCorrecto = true; // Si el nombre contiene solo letras y espacios, asignamos la variable a true
            }
            else{
                error(ERR_NAME);
                nombreCorrecto = false; // Si el nombre contiene caracteres no válidos, mostramos un error
                errorCarac++; 
            }
        }

        if(nombreCorrecto){
            while(nombre[0] == ' '){// Comprobamos si el nombre contiene espacios al principio
                nombre.erase(0, 1);
            } 

            while(nombre[nombre.size() - 1] == ' '){ // Comprobamos si el nombre contiene espacios al final
                nombre.erase(nombre.size() - 1, 1);
            } 

            if(nombre.size() < 3 || nombre.size() > KMAXNAME - 1){ // Comprobamos si el nombre tiene entre 3 y 19 caracteres
                error(ERR_NAME);
                nombreCorrecto = false;
            } 
            
            for(recorredor = 0; recorredor < (int)data.teachers.size(); recorredor++){ // Comprobamos si el nombre del profesor ya existe
                if(string(data.teachers[recorredor].name) == nombre){ // Comprobamos si el nombre del profesor ya existe
                    error(ERR_DUPLICATED); // Si el nombre del profesor ya existe, mostramos un error
                    nombreCorrecto = false;
                }
            }
        }
    } 
    while (!nombreCorrecto); // Si el nombre no es correcto, volvemos a pedir el nombre del profesor
}


void validarFila(string &linea, int &tipoError, int &contador, bool &hayError){ // Función que valida la línea. Se utiliza en la función batchAddQuestions y la auxiliar batchAddQuestionsComando
    int unidad;
    size_t pos1, pos2;
    bool convertido;

    contador = 0;
    tipoError = 0;
    hayError = false;
    convertido = false;


    if(linea.empty()){ // Comprobamos si la línea está vacía
        tipoError = 1;
        hayError = true;
        return;
    }

    for(char c : linea) { // Recorremos la línea
        if(c == '|') { // si encontramos el carácter '|'
            contador++; // Aumentamos el contador
        }
    }

    if (!isdigit(linea[0])) { // Comprobamos si la unidad es un número
        tipoError = 2;
        hayError = true;
        return;
    }

    if(isdigit(linea[0])){ // Comprobamos si la unidad es un número
        try{
            unidad = stoi(linea.substr(0, 1)); // Convertimos la unidad a entero
            convertido = true;
        }
        catch(const std::invalid_argument&){ // Si no se puede convertir a entero, mostramos un error
            tipoError = 2;
            hayError = true;
            return;
        }

        pos1 = linea.find('|'); // Buscamos la primera posición del carácter '|'

        if(pos1 != 1){
            tipoError = 2;
            hayError = true;
            return;
        }


        if(convertido){
            if(unidad > 5 || unidad < 1){ // Comprobamos si la unidad está entre 1 y 5
                tipoError = 2;
                hayError = true;
                return;
            }
        }
    }

    if(contador < 1){ // Comprobamos si hay menos de un '|'
        tipoError = 2;
        hayError = true;
        return;
    }

    if(contador > 2){ // Comprobamos si hay más de dos '|'
        tipoError = 2;
        hayError = true;
        return;
    }

    if(contador == 0){ // Si no hay '|'
        tipoError = 2;
        hayError = true;
        return;
    }


    if (contador == 2) { // Si hay dos '|'
        pos1 = linea.find('|'); // Buscamos la primera posición del carácter '|'
        while (pos1 != string::npos) { // Buscamos la segunda posición del carácter '|'
            pos2 = linea.find('|', pos1 + 1); 
            if (pos2 == string::npos || pos2 - pos1 == 1) {// Comprobamos si hay dos '|' seguidos
                tipoError = 2; // Si hay dos '|' seguidos, mostramos un error
                hayError = true;
                return;
            }
            pos1 = linea.find('|', pos2 + 1); // Buscamos la primera posición del carácter '|' a partir de la segunda posición
        }
    }


    if(contador == 1 || contador == 2){  // Si hay un '|' o dos '|'
        if(linea.back() == '|'){ // Comprobamos si la línea termina en '|'
                tipoError = 3;
                hayError = true;
                return;
        }
    }
}


void convertirCon(string &contrasenya){ // Función que convierte la contraseña. Se utiliza en la función addTeacher y addAnswers
    int recorredor;

    for(recorredor = 0; recorredor < (int)contrasenya.size(); recorredor++){
        switch(contrasenya[recorredor]){
            case '0':
                contrasenya[recorredor] = 'T';
                break;
            case '1':
                contrasenya[recorredor] = 'R';
                break;
            case '2':
                contrasenya[recorredor] = 'W';
                break;
            case '3':
                contrasenya[recorredor] = 'A';
                break;
            case '4':
                contrasenya[recorredor] = 'G';
                break;
            case '5':
                contrasenya[recorredor] = 'M';
                break;
            case '6':
                contrasenya[recorredor] = 'Y';
                break;
            case '7':
                contrasenya[recorredor] = 'F';
                break;
            case '8':
                contrasenya[recorredor] = 'P';
                break;
            case '9':
                contrasenya[recorredor] = 'D';
                break;
        }
    }
}


void batchAddQuestionsComando(Database &data, int &numData, const char *fileRef){ // Función que añade las preguntas a la base de datos. Se utiliza en al inicio del programa como argumento
    string fileName, // Nombre del fichero
        linea; // Línea del fichero
    int numLinea = 0, // Número de línea
        tipoError = 0, // Tipo de error
        contador,
        lineaError = 0,
        preguntasAñadidas = 1,
        errorN;
    bool hayError;

        fileName = fileRef;

        ifstream file(fileName); // Abrimos el fichero

        if (file.is_open()){ // Comprobamos si no se ha podido abrir el fichero
            errorN = 0;
            
            for(; getline(file, linea);){ // Leemos el fichero línea a línea
                numLinea++; // Aumentamos el número de línea

                validarFila(linea, tipoError, contador, hayError); // Validamos la línea

                if(tipoError == 1){
                    errorN++;
                }

                if(hayError && tipoError != 1){ // Si hay un error, mostramos el error
                    cout << "Error line" << numLinea << endl;
                    lineaError++;
                }
                if(!hayError){ // Si no hay errores, añadimos la pregunta a la base de datos
                    if(contador == 2){
                        Question pregunta;
                        size_t pos1, pos2;

                        pos1 = linea.find('|');
                        pos2 = linea.find('|', pos1 + 1);

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                        pregunta.answer = linea.substr(pos2 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;
                    }
                    else if(contador == 1){
                        Question pregunta;
                        size_t pos1;

                        pos1 = linea.find('|');

                        pregunta.unit = stoi(linea.substr(0, pos1));
                        pregunta.question = linea.substr(pos1 + 1);
                        pregunta.id = preguntasAñadidas;

                        data.questions.push_back(pregunta);
                        preguntasAñadidas++;

                    }
                }
            }

            summary(numLinea, lineaError, numData, errorN);
        }
        else{
            error(ERR_FILE); // Mostramos el error ERR_FILE
        }
}
