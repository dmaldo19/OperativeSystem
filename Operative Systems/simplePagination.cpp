//Diego Alberto Maldonado Melendez

#include <iostream>
#include <windows.h> //Libreria para limpiar pantalla, 
#include <queue> //Para usar cola, estructura de datos utilizada
#include <iomanip> //Libreria para definir cuantos decimales mostrar en la impresion
#include <random> //Libreria para generar valores random
#include <conio.h> //Libreria para kbhit
#include <string>
#include <vector>
#include <utility> //Libreria para usar pairs

using namespace std;

//Definicion de clase proceso, con los atributos requeridos
class proceso{
    private: //atributos
        int id;
        string operacion;
        int tiempoMaximo;
        int tiempoTranscurrido;
        double result;
        bool banderaRespuesta;
        int tiempoTranscurridoBloqueado;
        int tiempoLlegada;
        int tiempoFinal;
        int tiempoRespuesta;
        int tiempoServicio;
        int tamanioProceso;
        //Solo capturamos tiempo de llegada, de finalizacion, de respuesta y de servicio porque el
        //resto de tiempo los obtenemos con formulas
        

    //Metodos principalmente de asignacion y retorno, get y set.
    public:
        //Constructor
        proceso(int i, const string &o, int t, int tt, double r, bool bR, int ttb, int tl, int tf, int tr, int ts, int tp)
        : result(r){
            setId(i);
            setOperacion(o);
            setTiempoMaximo(t);
            setTiempoTranscurrido(tt);
            setBanderaRespuesta(bR);
            setTiempoTranscurridoBloqueado(ttb);
            setTiempoLlegada(tl);
            setTiempoFinal(tf);
            setTiempoRespuesta(tr);
            setTiempoServicio(ts);
            setTamanioProceso(tp);
        }

        void setId(int i){
            id = ( i < 0 ) ? 0 : i;
        }

        int getId() const{
            return id;
        }

        void setOperacion(const string &o){
            operacion = o;
        }

        string getOperacion() const{
            return operacion;
        }

        void setTiempoMaximo(int t){
            tiempoMaximo = (t < 0) ? 0: t;
        }

        int getTiempoMaximo() const{
            return tiempoMaximo;
        }

        void setTiempoTranscurrido(int tt){
            tiempoTranscurrido = (tt < 0) ? 0: tt;
        }

        int getTiempoTranscurrido() const{
            return tiempoTranscurrido;
        }

        void setResult(double r){
            result = r;
        }

        double getResult() const{
            return result;
        }

        void setBanderaRespuesta(bool br){
            banderaRespuesta = br;
        }

        bool getBanderaRespuesta() const{
            return banderaRespuesta;
        }

        void setTiempoTranscurridoBloqueado(int ttb){
            tiempoTranscurridoBloqueado = (ttb < 0) ? 0: ttb;
        }

        int getTiempoTranscurridoBloqueado() const{
            return tiempoTranscurridoBloqueado;
        }

        void setTiempoLlegada(int tl){
            tiempoLlegada = (tl < 0) ? 0: tl;
        }

        int getTiempoLlegada() const{
            return tiempoLlegada;
        }

        void setTiempoFinal(int tf){
            tiempoFinal = (tf < 0) ? 0: tf;
        }

        int getTiempoFinal() const{
            return tiempoFinal;
        }

        void setTiempoRespuesta(int tr){
            tiempoRespuesta = (tr < 0) ? 0: tr;
        }

        int getTiempoRespuesta() const{
            return tiempoRespuesta;
        }

        void setTiempoServicio(int ts){
            tiempoServicio = (ts < 0) ? 0: ts;
        }

        int getTiempoServicio() const{
            return tiempoServicio;
        }
        void setTamanioProceso(int tp){
            tamanioProceso = tp;
        }

        int getTamanioProceso() const{
            return tamanioProceso;
        }

};

// Función para posicionar el cursor en la pantalla
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Esta funcion permite que la terminal se ponga en pantalla completa cuando se inicie la ejecucion
void setConsoleToFullscreen() {
    HWND console = GetConsoleWindow();
    if (console != NULL) {
        ShowWindow(console, SW_MAXIMIZE); // Maximiza la ventana de la consola
        Sleep(100); // Pequeña pausa para permitir que la ventana se maximice completamente
    }
}

//Funcion para la realizacion de las operaciones, teniendo resultado double para
//divisiones principalmente
double computingOperation(int option, int a, int b){
    
    double result;
    switch (option){
        case 1: //Suma
            result = a + b;
            break;
        case 2: //Resta
            result = a - b;
            break;
        case 3: //Multiplicacion
            result = a * b;
            break;
        case 4: //Division
            result = static_cast<double>(a)/b;
            break;
        case 5: //Residuo
            result = a % b;
            break;
        case 6: //Porcentaje
            result = (a * b)/100;
            break;

        default:
            break;
    }
    return result;
}

void generarYAgregarProceso(queue<proceso>& colaProcesos, int id) {
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister 19937 como generador

    // Definir la primera distribución de la posible operacion a realizar
    uniform_int_distribution<int> distribucionOperacion(1, 6);
    //Definir el rango del tiempo, entre 6 y 18
    uniform_int_distribution<int> distribucionTiempo(6, 18);
    //Definir el tamanio del proceso entre 6 y 26
    uniform_int_distribution<int> distribucionTamanio(6, 26);

    //Ciclo para pedir los datos
    int operacion, tiempoMaximo, tamanioProceso;
    uniform_int_distribution<int> distribucion(-10, 10);
    
    int a = distribucion(gen);
    int b = distribucion(gen);
    string signo;
    double result;

    operacion = distribucionOperacion(gen);
    
    switch (operacion)
    {
    case 1:
        signo = to_string(a) + "+" + to_string(b);
        break;
    case 2:
        signo = to_string(a) + "-" + to_string(b);
        break;
    case 3:
        signo = to_string(a) + "*" + to_string(b);
        break;
    case 4:
        while (b == 0){
                b = distribucion(gen);
            }
        signo = to_string(a) + "/" + to_string(b);
        break;
    case 5:
        while (b == 0){
                b = distribucion(gen);
            }
        signo = to_string(a) + "%" + to_string(b);
        break;
    case 6:
        signo = to_string(a) + "P" + to_string(b);
        break;
    default:
        break;
    }
    result = computingOperation(operacion, a, b);//Invocamos funcion para que realice la operacion
    tiempoMaximo = distribucionTiempo(gen);
    tamanioProceso = distribucionTamanio(gen);

    //Instanciamos el objeto proceso que, posteriormente, sera aniadido a la cola
    proceso nuevoProceso(id, signo, tiempoMaximo, 0, result, false, 0, 0, 0, 0, 0, tamanioProceso);
    colaProcesos.push(nuevoProceso);
}

//Prototipo de funciones necesarias
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int tiempo, vector<pair<int, string>>& vectorProcesos, int& totalPagina);
proceso procesoEnEjecucion(queue<proceso>& EnEspera, int tiempoRespuesta);
int procesosPendientes(queue<proceso>& total);
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador, queue<proceso>& procesosBloqueados, int& id, int quantum, vector<pair<int, string>>& vectorProcesos, int& totalPagina);
void gestionarProcesoBloqueado(queue<proceso>& enBloqueado, queue<proceso>& enEspera);
void gestionarProcesoEnEspera(queue<proceso>& enEspera);
void mostrarTablaFinal(queue<proceso> procesoFinalizados);
void mostrarTablaParcial(queue<proceso> procesosFinalizados, queue<proceso> procesosEnEspera, queue<proceso> procesosEnBloqueado, queue<proceso> procesosNuevos, int contador, proceso enEjecucion);
void mostrarTablaPagina(vector<pair<int, string>>& vectorProcesos);
void gestionarProcesoFinal(vector<pair<int, string>>& vectorProcesos, int& totalPagina, proceso terminado);

int main(){
    setConsoleToFullscreen(); //Invocamos a que se ponga la pantalla completa
    int totalProcess = 0; //Todos los procesos que ingreso el usuario
    int quantum = 0; //valor del quantum
    queue<proceso> colaProcesos; //cola principal que almacenara todos los procesos, junto con la cola para mostrar la tabla momentanea
    gotoxy(0, 0); cout << "-----Programa de simulacion Round-Robin-----";
    gotoxy(0, 2); cout << "Ingrese la cantidad de procesos a realizar: ";
    cin >> totalProcess;
    gotoxy(0, 4); cout << "Ingrese el valor del Quantum: ";
    cin >> quantum;


    while(totalProcess < 1){ //Validacion por si no se meten procesos
        gotoxy(0, 4); cout << "Debe haber al menos un proceso. Intente nuevamente: ";
        cin >> totalProcess;
    }
    int id = 1;
    //Ciclo para pedir los datos
    for(int i = 1; i <= totalProcess; i++){
        generarYAgregarProceso(colaProcesos, id);
        id++;
    }

    //Creo las colas necesarias
    queue<proceso> EnEspera, Terminado, Bloqueados;

    //Tiempo total del programa
    int tiempo = 0;
    //Inicializacion del vector para tabla de paginas
    vector<pair<int, string>> vectorProcesos(40, make_pair(0, "-"));
    //Valor de llenado de mis paginas
    int totalPagina = 0;

    //Ciclo que se ejecutara hasta que la cola de procesos este vacia
    //Llenamos la cola de procesos en espera con el lote correspondiente
    ProcesoEnEspera(colaProcesos, EnEspera, tiempo, vectorProcesos, totalPagina);
    //El ciclo utiliza estructura do while porque puede haber un caso en el que
    //todos los posibles procesos esten en lista de espera, por ende, la lista
    //total esta vacia.
    do
    {
        //Ciclo para ejecutar todos los procesos en la lista de espera
        //Se agrego la validacion de si no esta vacia bloqueados porque
        //puede haber el caso de que todos los procesos en memoria esten bloqueados, y el ciclo debe seguir
        while (!EnEspera.empty() || !Bloqueados.empty()){
            system("cls");
            impresionesDeProcesos(colaProcesos, EnEspera, Terminado, tiempo, Bloqueados, id, quantum, vectorProcesos, totalPagina); //Invocamos funcion para mostrarlos
            queue<proceso> auxiliarTerminados = Terminado;
            //Imprimimos nuevamente debido a errores con el system("cls")
            int yf = 8;
            int finCicloF = auxiliarTerminados.size();
            for(int i = 0; i < finCicloF; i++){
                proceso elementoFinal = auxiliarTerminados.front();
                gotoxy(40+5, yf); cout << elementoFinal.getId();
                gotoxy(46+5, yf); cout << elementoFinal.getOperacion();
                if(elementoFinal.getResult()!= -77.0){
                    gotoxy(53+5, yf); cout << fixed << setprecision(1) << elementoFinal.getResult();
                } else {
                    gotoxy(53+5, yf); cout << "ER";
                }
                yf++;
                auxiliarTerminados.pop();
            }
        }
    } while (!colaProcesos.empty());
    
    //Llamamos a funcion para mostrar todos los tiempos
    mostrarTablaFinal(Terminado);
    return 0;
}

//Funcion que permite determinar cuales procesos pasaran a la lista de esperas
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int tiempo, vector<pair<int, string>>& vectorProcesos, int& totalPagina) {
    if (totalProcesos.empty()) {
        return;
    }
    int tamanioVector = vectorProcesos.size();
    for (int i = 0; !totalProcesos.empty() && i < tamanioVector; i++) {
        proceso elemento = totalProcesos.front();
        if (totalPagina + ((elemento.getTamanioProceso() + 4) / 5) * 5 > 200) {
            break;
        }
        proceso* nuevo = &totalProcesos.front();
        if (vectorProcesos[i].first == 0 ) {
            pair<int, string>& procesoPair = vectorProcesos[i];
            procesoPair.first = nuevo->getId();

            if (nuevo->getTamanioProceso() > 5){
                procesoPair.second = "5/5";
                nuevo->setTamanioProceso(nuevo->getTamanioProceso() - 5);
                totalPagina = totalPagina + 5;
            } else {
                procesoPair.second = to_string(nuevo->getTamanioProceso()) + "/5";
                nuevo->setTamanioProceso(elemento.getTamanioProceso());
                nuevo->setTiempoLlegada(tiempo);
                enEspera.push(elemento);
                totalProcesos.pop();
                totalPagina = totalPagina + 5;
            }
        }
    }
}

//Funcion para gestionar los procesos que pasen a bloqueados
void gestionarProcesoBloqueado(queue<proceso>& enBloqueado, queue<proceso>& enEspera) {

    //Realizamos una cola auxiliar en la cual, a cada proceso, le agregaremos 1 segundo en su atributo
    //transucrrido en bloqueado
    queue<proceso> colaModificada;
    while (!enBloqueado.empty()) {
        proceso proceso = enBloqueado.front();
        proceso.setTiempoTranscurridoBloqueado(proceso.getTiempoTranscurridoBloqueado() + 1);
        enBloqueado.pop();
        //si lleva menos de 8 segundo en bloqueado, se mantiene en bloqueo
        if(proceso.getTiempoTranscurridoBloqueado() <= 8){
            colaModificada.push(proceso);  // Agregar el proceso modificado a la cola auxiliar
        }else{ //de lo contrario, ya pasa a lista de espera
            //setteamos tiempo en bloqueado en 0 por si se vuelve a agregar el proceso en bloqueado
            proceso.setTiempoTranscurridoBloqueado(0);
            enEspera.push(proceso);
        }
    }
    //Igualamos la lista de bloqueados con la cola provisional que tiene las modificaciones de los tiempos
    enBloqueado = colaModificada;

}

//Funcion para mejor manejo de los proceso en espera
//esto ya que sufriran de mas cambios debido a los procesos bloqueados
void gestionarProcesoEnEspera(queue<proceso>& enEspera){
    //Procesos en espera
    //Impresiones con fines esteticos
    gotoxy(0, 8); cout << "            ";
    gotoxy(0, 9); cout << "            ";
    gotoxy(0, 10); cout << "            ";
    gotoxy(0, 11); cout << "            ";
    gotoxy(0, 12); cout << "            ";
    int y = 8;
    //Si la lista de espera no esta vacia, se muestran los datos correspondientes
    if(!enEspera.empty()){
        queue<proceso> auxiliar = enEspera;
        int finCicloI = auxiliar.size();
        for(int i = 0; i < finCicloI; i++){
            proceso elementoEspera = auxiliar.front();
            gotoxy(0, y); cout << elementoEspera.getId();
            gotoxy(4, y); cout << elementoEspera.getTiempoMaximo(); 
            gotoxy(9, y); cout << elementoEspera.getTiempoTranscurrido();
            auxiliar.pop();
            y++;
        }
    }
}

//Esta funcion permitira eliminar los procesos de la tabla de pagina una vez pasen a terminados
void gestionarProcesoFinal(vector<pair<int, string>>& vectorProcesos, int& totalPagina, proceso terminado){
    int tamanioVector = vectorProcesos.size();
    for(int i = 0; i < tamanioVector; i++){
        if (vectorProcesos[i].first == terminado.getId()){
            vectorProcesos[i].first = 0;
            vectorProcesos[i].second = "-";
            totalPagina = totalPagina - (((terminado.getTamanioProceso() + 4) / 5) * 5);
        }
    }
}

//Funcion que sirve para saber cual es el proceso que se va a ejecutar, tomando en cuenta la lista de espera
proceso procesoEnEjecucion(queue<proceso>& EnEspera, int tiempoRespuesta){
    //Si no esta vacia la lista de espera, se ejecuta el primer proceso en dicha lista
    if(!EnEspera.empty()){
        proceso enEjecucion = EnEspera.front();
        //si la bandera de respuesta es falsa, quiere decir que es la primera vez
        //que pasa a ejecucion, por ende, anotamos su tiempo de respuesta
        if (!enEjecucion.getBanderaRespuesta()){
            enEjecucion.setTiempoRespuesta(tiempoRespuesta);
        }
        //setteamos la bandera como true, para que, si vuelve a pasar el proceso a ejecucion, no tome ese tiempo como tiempo de espera
        enEjecucion.setBanderaRespuesta(true);
        return enEjecucion;
    } else{
        //validamos el proceso null en caso de que esten todos en bloqueado
        proceso enEjecucion(0, "NULL", 1, 0, 0.0, false, 8, 0, 0, 0, 0, 0);
        //el tiempo maximo estimado es de 1 para que pueda ingresar al ciclo donde tenemos el contador de segundos
        return enEjecucion;
    }
}

//Funcion que nos permite saber cuantos lotes faltan
int procesosPendientes(queue<proceso>& total){
    int tamano = static_cast<int>(total.size());
    return tamano;
}

//Funcion para mostrar los tiempos
void mostrarTablaFinal(queue<proceso> procesoFinalizados){
    system("cls");
    cout << "---------------------------------------------------Ejecucion de procesos------------------------------------------------------" << endl;
    cout << "ID    Operacion    Resultado    TME    T. Llegada    T. Finalizacion    T. Retorno"<<
    "    T. Respuesta    T. Servicio    T. Espera";
    int y = 3;
    int tamanioFinal = procesoFinalizados.size();
    //For que recorre todos los procesos realizados
    for(int i = 0; i < tamanioFinal; i++){
        proceso procesoFinal = procesoFinalizados.front();
        gotoxy(0, y); cout << procesoFinal.getId();
        gotoxy(6, y); cout << procesoFinal.getOperacion();
        if (procesoFinal.getResult() != -77.0){
            gotoxy(19, y); cout << fixed << setprecision(1) << procesoFinal.getResult();
        } else{
            gotoxy(19, y); cout << "Error";
        }
        gotoxy(32, y); cout << procesoFinal.getTiempoMaximo();
        gotoxy(39, y); cout << procesoFinal.getTiempoLlegada();
        gotoxy(54, y); cout << procesoFinal.getTiempoFinal();
        //Tiempo de retorno = finalizacion - llegada
        gotoxy(73, y); cout << procesoFinal.getTiempoFinal() - procesoFinal.getTiempoLlegada();
        //Tiempo de respuesta = hora respuesta - hora llegada
        gotoxy(87, y); cout << procesoFinal.getTiempoRespuesta() - procesoFinal.getTiempoLlegada();
        //Tiempo de servicio
        gotoxy(103, y); cout << procesoFinal.getTiempoServicio();
        //Tiempo de espera = tiempo retorno - servicio
        gotoxy(118, y); cout << procesoFinal.getTiempoFinal() - procesoFinal.getTiempoLlegada() - procesoFinal.getTiempoServicio();
        procesoFinalizados.pop();
        y++;
    }
    gotoxy(0, 30);
    system("pause");
}

//Funcion para mostrar los tiempos
void mostrarTablaParcial(queue<proceso> procesosFinalizados, queue<proceso> procesosEnEspera, queue<proceso> procesosEnBloqueado, queue<proceso> procesosNuevos, int contador, proceso enEjecucion){
    gotoxy(0, 0); cout << "---------------------------------------------------Tabla parcial------------------------------------------------------" << endl;
    gotoxy(0, 1); cout << "ID    Operacion    Resultado    TME    T. Llegada    T. Finalizacion    T. Retorno"<<
    "    T. Respuesta    T. Servicio    T. Espera";
    gotoxy(0, 2); cout << "---------------------------------------------------Finalizados------------------------------------------------------";
    int y = 3;
    int tamanioFinal = procesosFinalizados.size();
    queue<proceso> auxiliarTerminados = procesosFinalizados;
    //For que recorre todos los procesos realizados
    for(int i = 0; i < tamanioFinal; i++){
        proceso procesoFinal = auxiliarTerminados.front();
        gotoxy(0, y); cout << procesoFinal.getId();
        gotoxy(6, y); cout << procesoFinal.getOperacion();
        if (procesoFinal.getResult() != -77.0){
            gotoxy(19, y); cout << fixed << setprecision(1) << procesoFinal.getResult();
        } else{
            gotoxy(19, y); cout << "Error";
        }
        gotoxy(32, y); cout << procesoFinal.getTiempoMaximo();
        gotoxy(39, y); cout << procesoFinal.getTiempoLlegada();
        gotoxy(54, y); cout << procesoFinal.getTiempoFinal();
        //Tiempo de retorno = finalizacion - llegada
        gotoxy(73, y); cout << procesoFinal.getTiempoFinal() - procesoFinal.getTiempoLlegada();
        //Tiempo de respuesta = hora respuesta - hora llegada
        gotoxy(87, y); cout << procesoFinal.getTiempoRespuesta() - procesoFinal.getTiempoLlegada();
        //Tiempo de servicio
        gotoxy(103, y); cout << procesoFinal.getTiempoServicio();
        //Tiempo de espera = tiempo retorno - servicio
        gotoxy(118, y); cout << procesoFinal.getTiempoFinal() - procesoFinal.getTiempoLlegada() - procesoFinal.getTiempoServicio();
        auxiliarTerminados.pop();
        y++;
    }
    y+=2;
    gotoxy(0, y); cout << "-----------------------------------------------Procesos en Ejecucion---------------------------------------------------" << endl;
    y++;
    gotoxy(0, y); cout << enEjecucion.getId();
    gotoxy(6, y); cout << enEjecucion.getOperacion();
    gotoxy(32, y); cout << enEjecucion.getTiempoMaximo();
    gotoxy(39, y); cout << enEjecucion.getTiempoLlegada();
    gotoxy(87, y); cout << enEjecucion.getTiempoRespuesta() - enEjecucion.getTiempoLlegada();
    //Tiempo de servicio
    gotoxy(103, y); cout << enEjecucion.getTiempoServicio();
    //Tiempo de espera = contador - llegada - servicio
    gotoxy(118, y); cout << contador - enEjecucion.getTiempoLlegada() - enEjecucion.getTiempoServicio();
    y++;
    y+=2;
    gotoxy(0, y); cout << "-------------------------------------------------Procesos en Espera----------------------------------------------------" << endl;
    y++;
    int tamanioFinalEspera = procesosEnEspera.size();
    queue<proceso> auxiliarEspera = procesosEnEspera;
    for(int i = 0; i < tamanioFinalEspera; i++){
        proceso procesoEnEspera = auxiliarEspera.front();
        gotoxy(0, y); cout << procesoEnEspera.getId();
        gotoxy(6, y); cout << procesoEnEspera.getOperacion();
        gotoxy(32, y); cout << procesoEnEspera.getTiempoMaximo();
        gotoxy(39, y); cout << procesoEnEspera.getTiempoLlegada();
        //Tiempo de respuesta = hora respuesta - hora llegada
        if(procesoEnEspera.getTiempoRespuesta() - procesoEnEspera.getTiempoLlegada() > 0){
            gotoxy(87, y); cout << procesoEnEspera.getTiempoRespuesta() - procesoEnEspera.getTiempoLlegada();
        }
        //Tiempo de servicio
        gotoxy(103, y); cout << procesoEnEspera.getTiempoServicio();
        //Tiempo de espera = contador - llegada - servicio
        gotoxy(118, y); cout << contador - procesoEnEspera.getTiempoLlegada() - procesoEnEspera.getTiempoServicio();
        auxiliarEspera.pop();
        y++;
    }
    y+=2;
    gotoxy(0, y); cout << "-------------------------------------------------Procesos Bloqueado-----------------------------------------------------" << endl;
    y++;
    int tamanioFinalBloqueado = procesosEnBloqueado.size();
    queue<proceso> auxiliarBloqueados = procesosEnBloqueado;
    for(int i = 0; i < tamanioFinalBloqueado; i++){
        proceso procesoBloqueado = auxiliarBloqueados.front();
        gotoxy(0, y); cout << procesoBloqueado.getId();
        gotoxy(6, y); cout << procesoBloqueado.getOperacion();
        gotoxy(32, y); cout << procesoBloqueado.getTiempoMaximo();
        gotoxy(39, y); cout << procesoBloqueado.getTiempoLlegada();
        //Tiempo de respuesta = hora respuesta - hora llegada
        if(procesoBloqueado.getTiempoRespuesta() - procesoBloqueado.getTiempoLlegada() > 0){
            gotoxy(87, y); cout << procesoBloqueado.getTiempoRespuesta() - procesoBloqueado.getTiempoLlegada();
        }
        gotoxy(54, y); cout << "TT en Bloqueado: " << procesoBloqueado.getTiempoTranscurridoBloqueado();
        //Tiempo de servicio
        gotoxy(103, y); cout << procesoBloqueado.getTiempoServicio();
        //Tiempo de espera = contador - llegada - servicio
        gotoxy(118, y); cout << contador - procesoBloqueado.getTiempoLlegada() - procesoBloqueado.getTiempoServicio();
        auxiliarBloqueados.pop();
        y++;
    }
    y+=2;
    gotoxy(0, y); cout << "---------------------------------------------------Procesos Nuevos------------------------------------------------------" << endl;
    y++;
    int tamanioFinalNuevos = procesosNuevos.size();
    queue<proceso> auxiliarNuevos = procesosNuevos;
    for(int i = 0; i < tamanioFinalNuevos; i++){
        proceso procesoNuevo = auxiliarNuevos.front();
        gotoxy(0, y); cout << procesoNuevo.getId();
        gotoxy(6, y); cout << procesoNuevo.getOperacion();
        gotoxy(32, y); cout << procesoNuevo.getTiempoMaximo();
        auxiliarNuevos.pop();
        y++;
    }
}

void mostrarTablaPagina(vector<pair<int, string>>& vectorProcesos){
    int ypagina = 4;
    gotoxy(70, 2); cout << "---------Tabla de Paginas---------";
    gotoxy(70, 3); cout << "Frame   Tamanio     ID";
    for(int i = 1; i <= 44; i++){
        gotoxy(70, ypagina); cout << i;
        ypagina++;
    }
    for(int i = 44; i > 40; i--){
        ypagina--;
        gotoxy(78, ypagina); cout << "Sistema Operativo";
    }
    ypagina = 4;
    int tamanioVector = vectorProcesos.size();
    for (int i = 0; i < tamanioVector; i++){
        gotoxy(78, ypagina); cout << vectorProcesos[i].second;
        gotoxy(90, ypagina); cout << vectorProcesos[i].first;
        ypagina++;
    }
}

//Funcion para imprimir todos los procesos
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador, queue<proceso>& procesosBloqueados, int& id, int quantum, vector<pair<int, string>>& vectorProcesos, int& totalPagina) {
    //cada vez que entre, se asignara un nuevo proceso a ejecutar
    proceso enEjecucion = procesoEnEjecucion(espera, contador);
    if(!espera.empty()){ 
        espera.pop();
    }

    queue<proceso> auxiliarTerminados = final;
    int yf = 8;
    int finCicloF = auxiliarTerminados.size();
    for(int i = 0; i < finCicloF; i++){
        proceso elementoFinal = auxiliarTerminados.front();
        gotoxy(40+5, yf); cout << elementoFinal.getId();
        gotoxy(46+5, yf); cout << elementoFinal.getOperacion();
        if(elementoFinal.getResult()!= -77.0){
            gotoxy(53+5, yf); cout << fixed << setprecision(1) << elementoFinal.getResult();
        } else {
            gotoxy(53+5, yf); cout << "ER";
        }
        yf++;
        auxiliarTerminados.pop();
    }

    //Contador para llevar el quantum
    int contadorQuantum = 0;

    //Proceso en ejecucion
    //for principal donde cambian los segundos
    for (int i = enEjecucion.getTiempoTranscurrido(); i < enEjecucion.getTiempoMaximo(); i++){
        if (contadorQuantum >= quantum) {
            // La condición de contadorQuantum se cumple, salimos del bucle
            espera.push(enEjecucion);
            break;
        }
         //Impresiones para mostrar los valores pertinentes
        gotoxy(0,2); cout << "----------------------Ejecucion de procesos-------------------------";
        //Procesos en espera
        gotoxy(0,6); cout << "Proceso listo";
        gotoxy(0,7); cout << "ID  TME  TT";
        //Terminados
        gotoxy(45, 6); cout << ("Terminados");
        gotoxy(40+5, 7); cout << ("ID");
        gotoxy(46+5, 7); cout << ("Ope");
        gotoxy(53+5, 7); cout << ("Res");

        
        gotoxy(0,4); cout << "N. De procesos pendiente: " << procesosPendientes(total) << "     Valor del quantum: " << quantum;
        gotoxy(15,25); cout << "Tiempo total: " << contador;
        gotoxy(15,6); cout << "Proceso en ejecucion";
        gotoxy(15,7); cout << "ID: " << enEjecucion.getId();
        gotoxy(15,8); cout << "Ope: "<< enEjecucion.getOperacion();
        gotoxy(15,9); cout << "TME: " << enEjecucion.getTiempoMaximo();
        gotoxy(15,10); cout << "TT: " << i << "  ";
        gotoxy(15,11); cout << "TR: " << enEjecucion.getTiempoMaximo() - i << "  ";
        // Espera hasta que el cronómetro avance un segundo
        enEjecucion.setTiempoTranscurrido(i + 1);
        enEjecucion.setTiempoServicio(i+1);
        //Realizamos diferencias entre tiempo transcurrido y tiempo de servicio ya que
        //el tiempo transcurrido lo usamos para efectos logicos, mientras que el de servicio
        //es el que se muestra en la tabla final

        //mostramos procesos en espera
        gestionarProcesoEnEspera(espera);

        //mostramos procesos bloqueados
        gestionarProcesoBloqueado(procesosBloqueados, espera);

        //Mostramos tabla de paginas
        mostrarTablaPagina(vectorProcesos);

        //Mostrar el proceso siguiente para ver por que no puede ingresar
        if(!(total.empty())){
            proceso procesoSiguiente = total.front();
            gotoxy(120, 2); cout << "Proceso tratando de entrar -> Id: " << procesoSiguiente.getId() << " Tam: " << procesoSiguiente.getTamanioProceso();
        }

        //avanzamos 1 segundo
        Sleep(1000);
        contador++;
        contadorQuantum++;

        //funcion para la deteccion de teclas
        if(kbhit()){
            char key = getch();
            switch (key)
            {
                case 'i':
                    //igualando i al tiempo maximo, el proceso sale del ciclo
                    i = enEjecucion.getTiempoMaximo();
                    procesosBloqueados.push(enEjecucion);
                    break;
                case 'e':
                    //salimos del ciclo
                    i = enEjecucion.getTiempoMaximo();
                    //decimos que su tiempo transcurrido es = tme para efectos logicos
                    enEjecucion.setTiempoTranscurrido(enEjecucion.getTiempoMaximo());
                    //los resultados erroneos lo asignamos como -77
                    enEjecucion.setResult(-77);
                    break;
                //para crear proceso nuevo
                case 'n':
                    generarYAgregarProceso(total, id);
                    ProcesoEnEspera(total, espera, contador, vectorProcesos, totalPagina);
                    id++;
                    break;
                //para la pausa
                case 'p':
                    while (1){
                        if(kbhit()){
                            key = getch();
                            if (key == 'c'){
                                break;
                            }
                        }
                    }
                    break;
                case 't':
                    while (1){
                        if(kbhit()){
                            key = getch();
                            if (key == 'c'){
                                break;
                            }
                        }
                    }
                    break;
                //para la tabla parcial
                case 'b':
                    system("cls");
                    while(1){
                        mostrarTablaParcial(final, espera, procesosBloqueados, total, contador, enEjecucion);
                        if(kbhit()){
                            key = getch();
                            if (key == 'c'){
                                system("cls");
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }

        }
        
    }
    //si el tiempo transcurrido es menor al tme, el proceso se va a bloqueados
    if (!(enEjecucion.getTiempoTranscurrido() < enEjecucion.getTiempoMaximo())){

        if(enEjecucion.getId() != 0){
            //como ya salio de memoria, otro proceso nuevo se agrega a la lista de espera
            gestionarProcesoFinal(vectorProcesos, totalPagina, enEjecucion);
            ProcesoEnEspera(total, espera, contador, vectorProcesos, totalPagina);
            //setteeamos tiempos finales
            enEjecucion.setTiempoFinal(contador);
            final.push(enEjecucion);
        }
    }
    //impresion con efectos esteticos
    gotoxy(15,6); cout << "Proceso en ejecucion";
    gotoxy(15,7); cout << "ID:    ";
    gotoxy(15,8); cout << "Ope:        ";
    gotoxy(15,9); cout << "TME:    ";
    gotoxy(15,10); cout << "TT:    ";
    gotoxy(15,11); cout << "TR:    ";

}