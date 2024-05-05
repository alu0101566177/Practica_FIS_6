# Practica_FIS_6

Prototipo de biblioteca virtual

[Primera iteración del proyecto](https://github.com/alu0101566177/Practica_FIS_6/tree/8a64f14d008ac866c0011a757106c6fa7eab57ac)

[Segunda iteración del proyecto](https://github.com/alu0101566177/Practica_FIS_6/tree/main)

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
- `utils/`: Contiene pequeñas utilidades.
- `router/`: Contiene rutas HTTP estáticas y dinámicas para un mejor desarrollo de la API REST. 

## Compilación y ejecución

Para la compilación y ejecución se usa la herramienta **make**:

```sh
$ make run
```
