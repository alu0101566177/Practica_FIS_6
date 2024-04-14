# Practica_FIS_6

Prototipo de biblioteca virtual

## Dependencias

Para compilar y ejecutar este proyecto es necesario instalar la libreria Asio C++, y la base de datos SQLite:

```sh
# Distribuciones Debian, basadas en Ubuntu
sudo apt install libasio-dev sqlite3
# Distribuciones basadas en Arch
sudo pacman -S asio sqlite
```

## Estructura del Directorio `src/`

La carpeta `src/` contiene las siguientes subcarpetas:

- `controllers/`: Almacena los controladores de las aplicaciones web.
- `db/`: Contiene los archivos de configuración y código relacionado con la base de datos.
- `models/`: Define los modelos de datos de la aplicación.
- `static/`: Contiene los recursos estáticos de la aplicación, como imágenes, hojas de estilo y archivos JavaScript.
- `templates/`: Almacena las plantillas HTML utilizadas para generar las vistas de la aplicación.
- `views/`: Contiene las vistas de la aplicación, las cuales combinan plantillas HTML con datos dinámicos.
- `utils/`: Contiene pequeñas utilidades

## Compilación y ejecución

Para la compilación se usa la herramienta **make**:

```sh
$ make clean
$ make
$ cd bin
$ ./server
```
