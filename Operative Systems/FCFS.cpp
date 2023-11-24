//Diego Alberto Maldonado Melendez
//Seccion D04

#include <iostream>
#include <windows.h> //Libreria para limpiar pantalla, 
#include <queue> //Para usar cola, estructura de datos utilizada
#include <iomanip> //Libreria para definir cuantos decimales mostrar en la impresion
#include <random> //Libreria para generar valores random
#include <conio.h> //Libreria para kbhit
#include <string>

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
        //Solo capturamos tiempo de llegada, de finalizacion, de respuesta y de servicio porque el
        //resto de tiempo los obtenemos con formulas
        

    //Metodos principalmente de asignacion y retorno, get y set.
    public:
        //Constructor
        proceso(int i, const string &o, int t, int tt, double r, bool bR, int ttb, int tl, int tf, int tr, int ts)
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

//Prototipo de funciones necesarias
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int cantidadProcesos, int tiempo);
void recargarEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int tiempo);
proceso procesoEnEjecucion(queue<proceso>& EnEspera, int tiempoRespuesta);
int procesosPendientes(queue<proceso>& total);
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador, queue<proceso>& procesosBloqueados);
void gestionarProcesoBloqueado(queue<proceso>& enBloqueado, queue<proceso>& enEspera);
void gestionarProcesoEnEspera(queue<proceso>& enEspera);
void mostrarTablaFinal(queue<proceso> procesoFinalizados);

int main(){
    setConsoleToFullscreen(); //Invocamos a que se ponga la pantalla completa
    int totalProcess = 0; //Todos los procesos que ingreso el usuario
    queue<proceso> colaProcesos; //cola principal que almacenara todos los procesos
    gotoxy(0, 0); cout << "-----Programa de simulacion de procesamiento por lote-----";
    gotoxy(0, 2); cout << "Ingrese la cantidad de procesos a realizar: ";
    cin >> totalProcess;

    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister 19937 como generador

    // Definir la primera distribución de la posible operacion a realizar
    uniform_int_distribution<int> distribucionOperacion(1, 6);
    //Definir el rango del tiempo, entre 6 y 18
    uniform_int_distribution<int> distribucionTiempo(6, 18);

    while(totalProcess < 1){ //Validacion por si no se meten procesos
        gotoxy(0, 4); cout << "Debe haber al menos un proceso. Intente nuevamente: ";
        cin >> totalProcess;
    }

    //Ciclo para pedir los datos
    for(int i = 1; i <= totalProcess; i++){
        system("cls");
        int id, operacion, tiempoMaximo;
        uniform_int_distribution<int> distribucion(-10, 10);
        // Crear un generador de números aleatorios
        random_device rd;
        mt19937 gen(rd()); // Mersenne Twister 19937 como generador
        //Generamos dos enteros random para las operaciones
        int a = distribucion(gen);
        int b = distribucion(gen);
        string signo;
        double result;

        id = i;

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

        //Instanciamos el objeto proceso que, posteriormente, sera aniadido a la cola
        proceso nuevoProceso(id, signo, tiempoMaximo, 0, result, false, 0, 0, 0, 0, 0);
        colaProcesos.push(nuevoProceso);
    }

    //Creo las colas necesarias
    queue<proceso> EnEspera, Terminado, Bloqueados;

    //Tiempo total del programa
    int tiempo = 0;

    //Ciclo que se ejecutara hasta que la cola de procesos este vacia
    //Llenamos la cola de procesos en espera con el lote correspondiente
    ProcesoEnEspera(colaProcesos, EnEspera, totalProcess, tiempo);
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
            impresionesDeProcesos(colaProcesos, EnEspera, Terminado, tiempo, Bloqueados); //Invocamos funcion para mostrarlos
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
void ProcesoEnEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int cantidadProcesos, int tiempo) {
    if (totalProcesos.empty()) {
        return; // No hay elementos en totalProcesos, no se puede hacer nada
    }
    //Si hay mas de 5 procesos, usamos un for para cargar los primeros 5
    if (cantidadProcesos > 5){
        for(int i = 0; i < 5 && i < cantidadProcesos; i++){
            proceso nuevo = totalProcesos.front();
            nuevo.setTiempoLlegada(tiempo);
            totalProcesos.pop();
            enEspera.push(nuevo);
        }
    //Si son menos de 5 procesos, todos los procesos pasan a memoria,
    //esto ya que 5 es la cantidad maxima de procesos en memoria segun la actividad
    } else{
        for(int i = 0; i < cantidadProcesos && i < cantidadProcesos; i++){
            proceso nuevo = totalProcesos.front();
            nuevo.setTiempoLlegada(tiempo);
            totalProcesos.pop();
            enEspera.push(nuevo);
        }
    }
    
}

//Ahora, como al terminar un proceso, pasa otro proceso de nuevo a listo, requerimos funcion
//que determine cual sera el nuevo proceso a cargar en memoria
void recargarEspera(queue<proceso>& totalProcesos, queue<proceso>& enEspera, int tiempo){
    if (totalProcesos.empty()) {
        return; // No hay elementos en totalProcesos, no se puede hacer nada
    }
    //al ser FCFS, el que se encuentre primero en la cola de todos los procesos sera
    //el siguiente a pasar a memoria
    proceso procesoListo = totalProcesos.front();
    procesoListo.setTiempoLlegada(tiempo);
    //Lo agregamos a la lista de espera, o sea, a memoria
    enEspera.push(procesoListo);
    totalProcesos.pop();
}

//Funcion para gestionar los procesos que pasen a bloqueados
void gestionarProcesoBloqueado(queue<proceso>& enBloqueado, queue<proceso>& enEspera) {
    int tamanioBloqueado = enBloqueado.size();
    queue<proceso> auxiliarBloqueados = enBloqueado;
    int yBloqueados = 17;
    //Las siguientes impresiones son para cuestiones esteticas
    gotoxy(0, 17); cout << "                                     ";
    gotoxy(0, 18); cout << "                                     ";
    gotoxy(0, 19); cout << "                                     ";
    gotoxy(0, 20); cout << "                                     ";
    gotoxy(0, 21); cout << "                                     ";
    //for que recorre los procesos bloqueados y los muestra
    for(int i = 0; i < tamanioBloqueado; i++){
        proceso procesoBloqueado = auxiliarBloqueados.front();
        gotoxy(0, yBloqueados); cout << procesoBloqueado.getId();
        gotoxy(7, yBloqueados); cout << procesoBloqueado.getTiempoTranscurridoBloqueado();
        auxiliarBloqueados.pop();
        yBloqueados++;
    }

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
        proceso enEjecucion(0, "NULL", 1, 0, 0.0, false, 8, 0, 0, 0, 0);
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

//Funcion para imprimir todos los procesos
void impresionesDeProcesos(queue<proceso>& total, queue<proceso>& espera, queue<proceso>& final, int& contador, queue<proceso>& procesosBloqueados) {
    //cada vez que entre, se asignara un nuevo proceso a ejecutar
    proceso enEjecucion = procesoEnEjecucion(espera, contador);
    if(!espera.empty()){ 
        espera.pop();
    }

    //Impresiones para mostrar los valores pertinentes
    gotoxy(0,2); cout << "----------------------Ejecucion de procesos-------------------------";
    gotoxy(0,4); cout << "N. De procesos pendiente: " << procesosPendientes(total);
    //Procesos en espera
    gotoxy(0,6); cout << "Lote Actual";
    gotoxy(0,7); cout << "ID  TME  TT";
    //Terminados
    gotoxy(45, 6); cout << ("Terminados");
    gotoxy(40+5, 7); cout << ("ID");
    gotoxy(46+5, 7); cout << ("Ope");
    gotoxy(53+5, 7); cout << ("Res");

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

    //Procesos en bloqueado
    gotoxy(0,15); cout << "Bloqueados";
    gotoxy(0,16); cout << "ID     TTB";

    //Proceso en ejecucion
    //for principal donde cambian los segundos
    for (int i = enEjecucion.getTiempoTranscurrido(); i < enEjecucion.getTiempoMaximo(); i++){
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

        //avanzamos 1 segundo
        Sleep(1000);
        contador++;

        //funcion para la deteccion de teclas
        if(kbhit()){
            char key = getch();
            switch (key)
            {
                case 'i':
                    //igualando i al tiempo maximo, el proceso sale del ciclo
                    i = enEjecucion.getTiempoMaximo();
                    break;
                case 'e':
                    //salimos del ciclo
                    i = enEjecucion.getTiempoMaximo();
                    //decimos que su tiempo transcurrido es = tme para efectos logicos
                    enEjecucion.setTiempoTranscurrido(enEjecucion.getTiempoMaximo());
                    //los resultados erroneos lo asignamos como -77
                    enEjecucion.setResult(-77);
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
                default:
                    break;
            }

        }
    }
    //si el tiempo transcurrido es menor al tme, el proceso se va a bloqueados
    if(enEjecucion.getTiempoTranscurrido() < enEjecucion.getTiempoMaximo()){
        procesosBloqueados.push(enEjecucion);
    } else{ //sino, se va a terminado
        if(enEjecucion.getId() != 0){
            //como ya salio de memoria, otro proceso nuevo se agrega a la lista de espera
            recargarEspera(total, espera, contador);
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