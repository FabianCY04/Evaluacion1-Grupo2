# 1. INAGEN BASE: Descargamos un entorno Linux que ya incluye el compilador de C/C++
FROM gcc:latest
# 2. DIRECTORIO DE TRABAJO: Creamos una carpeta llamada /app dentro del contenedor
WORKDIR /app
# 3. COPIA DE ARCHIVOS: Copiamos nuestro main.cpp (y todo lo demss) a la carpeta /app del contenedor
COPY . /app
# 4. COMPILACIÓN: Compflamos los archivos .cpp y generamos un ejecutable llamado "programa_grupo"
RUN g++ -o programa_grupo *.cpp