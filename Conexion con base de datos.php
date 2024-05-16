<?php
$servername = "localhost"; // Cambia esto si tu servidor de base de datos es diferente
$username = "your_username";
$password = "your_password";
$dbname = "pet_feeder";

// Crear conexión
$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

// Obtener datos del POST
$distance = $_POST['distance'];

// Insertar datos
$sql = "INSERT INTO refill_log (distance) VALUES ('$distance')";

if ($conn->query($sql) === TRUE) {
    echo "Nuevo registro creado con éxito";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>