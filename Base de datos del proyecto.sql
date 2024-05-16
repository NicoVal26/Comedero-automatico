CREATE DATABASE pet_feeder;
USE pet_feeder;
CREATE TABLE refill_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    distance FLOAT
);