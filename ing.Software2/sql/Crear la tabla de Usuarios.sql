-- Crear la tabla de Usuarios
CREATE TABLE Usuarios (
    UsuarioID INT PRIMARY KEY AUTO_INCREMENT,
    Nombre VARCHAR(50),
    Apellidos VARCHAR(50),
    Email VARCHAR(100),
    Contraseña VARCHAR(100),
    FechaNacimiento DATE,
    TipoUsuario VARCHAR(20)
);

-- Insertar datos en la tabla de Usuarios
INSERT INTO Usuarios (Nombre, Apellidos, Email, Contraseña, FechaNacimiento, TipoUsuario)
VALUES
    ('Juan', 'Pérez', 'juan@ikrea.com', 'pass1', '1990-01-01', 'Administrador'),
    ('María', 'García', 'maria@ikrea.com', 'pass2', '1991-02-02', 'Bibliotecario'),
    ('Pedro', 'López', 'pedro@ikrea.com', 'pass3', '1992-03-03', 'Usuario Normal'),
    ('Laura', 'Sánchez', 'laura@ikrea.com', 'pass4', '1985-04-04', 'Usuario Normal'),
    ('Carlos', 'Martínez', 'carlos@ikrea.com', 'pass5', '1980-05-05', 'Usuario Normal'),
    ('Elena', 'Ramírez', 'elena@ikrea.com', 'pass6', '1975-06-06', 'Usuario Normal'),
    ('Sofía', 'González', 'sofia@ikrea.com', 'pass7', '1970-07-07', 'Usuario Normal'),
    ('Luis', 'Torres', 'luis@ikrea.com', 'pass8', '1965-08-08', 'Usuario Normal'),
    ('Ana', 'Fernández', 'ana@ikrea.com', 'pass9', '1960-09-09', 'Usuario Normal'),
    ('David', 'Díaz', 'david@ikrea.com', 'pass10', '1955-10-10', 'Usuario Normal'),
    ('Isabel', 'Vargas', 'isabel@ikrea.com', 'pass11', '1950-11-11', 'Usuario Normal'),
    ('Javier', 'Luna', 'javier@ikrea.com', 'pass12', '1945-12-12', 'Usuario Normal'),
    ('Carmen', 'Soto', 'carmen@ikrea.com', 'pass13', '1940-01-13', 'Usuario Normal'),
    ('Jorge', 'Blanco', 'jorge@ikrea.com', 'pass14', '1935-02-14', 'Usuario Normal'),
    ('Marta', 'Ortega', 'marta@ikrea.com', 'pass15', '1930-03-15', 'Usuario Normal'),
    ('Raúl', 'Fuentes', 'raul@ikrea.com', 'pass16', '1925-04-16', 'Usuario Normal'),
    ('Teresa', 'Cabrera', 'teresa@ikrea.com', 'pass17', '1920-05-17', 'Usuario Normal'),
    ('Sergio', 'Giménez', 'sergio@ikrea.com', 'pass18', '1915-06-18', 'Usuario Normal'),
    ('Celia', 'Silva', 'celia@ikrea.com', 'pass19', '1910-07-19', 'Usuario Normal'),
    ('Alberto', 'Rojas', 'alberto@ikrea.com', 'pass20', '1905-08-20', 'Usuario Normal');

-- Crear la tabla de Títulos
CREATE TABLE Titulos (
    TituloID INT PRIMARY KEY AUTO_INCREMENT,
    Titulo VARCHAR(100),
    Autor VARCHAR(100),
    Genero VARCHAR(50),
    FechaPublicacion DATE
);

-- Insertar datos en la tabla de Títulos
INSERT INTO Titulos (Titulo, Autor, Genero, FechaPublicacion)
VALUES
    ('El Quijote', 'Miguel de Cervantes', 'Novela', '1605-01-01'),
    ('La Divina Comedia', 'Dante Alighieri', 'Poesía Épica', '1321-01-01'),
    ('Hamlet', 'William Shakespeare', 'Drama', '1603-01-01'),
    ('1984', 'George Orwell', 'Ciencia Ficción', '1949-01-01'),
    ('Cien Años de Soledad', 'Gabriel García Márquez', 'Realismo Mágico', '1967-01-01'),
    ('Don Quijote', 'Miguel de Cervantes', 'Novela', '1605-01-01'),
    ('Ulises', 'James Joyce', 'Ficción Modernista', '1922-01-01'),
    ('Matar a un Ruiseñor', 'Harper Lee', 'Novela Clásica', '1960-01-01'),
    ('Crimen y Castigo', 'Fyodor Dostoevsky', 'Novela Psicológica', '1866-01-01'),
    ('En Busca del Tiempo Perdido', 'Marcel Proust', 'Novela Modernista', '1913-01-01'),
    ('Orgullo y Prejuicio', 'Jane Austen', 'Novela Romántica', '1813-01-01'),
    ('El Gran Gatsby', 'F. Scott Fitzgerald', 'Novela Modernista', '1925-01-01'),
    ('Moby-Dick', 'Herman Melville', 'Novela Aventura', '1851-01-01'),
    ('Las Uvas de la Ira', 'John Steinbeck', 'Novela Realista', '1939-01-01'),
    ('La Odisea', 'Homer', 'Poesía Épica', 'Antigua'),
    ('La Ilíada', 'Homer', 'Poesía Épica', 'Antigua'),
    ('El Gran Inquisidor', 'Fyodor Dostoevsky', 'Ficción Filosófica', '1880-01-01'),
    ('Canción de Hielo y Fuego', 'George R.R. Martin', 'Fantasía Épica', '1996-01-01'),
    ('Harry Potter y la Piedra Filosofal', 'J.K. Rowling', 'Fantasía', '1997-01-01'),
    ('Código Da Vinci', 'Dan Brown', 'Misterio', '2003-01-01');

-- Crear la tabla de Ejemplares
CREATE TABLE Ejemplares (
    EjemplarID INT PRIMARY KEY AUTO_INCREMENT,
    TituloID INT,
    Estado VARCHAR(20),
    FechaPrestamo DATE,
    FechaDevolucion DATE
);

-- Insertar datos en la tabla de Ejemplares
-- Para cada título, se insertan tres ejemplares disponibles
INSERT INTO Ejemplares (TituloID, Estado, FechaPrestamo, FechaDevolucion)
SELECT TituloID, 'Disponible', NULL, NULL FROM Titulos;

-- Crear la tabla de Préstamos
CREATE TABLE Prestamos (
    PrestamoID INT PRIMARY KEY AUTO_INCREMENT,
    UsuarioID INT,
    EjemplarID INT,
    FechaPrestamo DATE,
    FechaDevolucion DATE
);

-- Insertar datos en la tabla de Préstamos
-- Varios préstamos realizados por diferentes usuarios
INSERT INTO Prestamos (UsuarioID, EjemplarID, FechaPrestamo, FechaDevolucion)
VALUES
    (2, 1, '2023-07-20', NULL),
    (3, 2, '2023-07-21', NULL),
    (4, 3, '2023-07-22', NULL),
    (5, 4, '2023-07-23', NULL),
    (6, 5, '2023-07-24', NULL),
    (7, 6, '2023-07-25', NULL),
    (8, 7, '2023-07-26', NULL),
    (9, 8, '2023-07-27', NULL),
    (10, 9, '2023-07-28', NULL),
    (11, 10, '2023-07-29', NULL),
    (12, 11, '2023-07-30', NULL),
    (13, 12, '2023-07-31', NULL),
    (14, 13, '2023-08-01', NULL),
    (15, 14, '2023-08-02', NULL),
    (16, 15, '2023-08-03', NULL),
    (17, 16, '2023-08-04', NULL),
    (18, 17, '2023-08-05', NULL),
    (19, 18, '2023-08-06', NULL),
    (20, 19, '2023-08-07', NULL);
