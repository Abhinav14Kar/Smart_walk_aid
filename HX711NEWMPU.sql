CREATE DATABASE ghost;
CREATE TABLE ghost.mydata (
    id INT AUTO_INCREMENT PRIMARY KEY,
    weight FLOAT,
    ax FLOAT,
    ay FLOAT,
    az FLOAT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
DROP TABLE IF EXISTS ghost.mydata;
DROP DATABASE IF EXISTS ghost;
CREATE DATABASE ghost;
CREATE TABLE ghost.mydata (
    id INT AUTO_INCREMENT PRIMARY KEY,
    weight FLOAT,
    ax FLOAT,
    ay FLOAT,
    az FLOAT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
SELECT * FROM ghost.mydata;
UPDATE ghost.mydata
SET weight = ROUND(weight, 4),
    ax = ROUND(ax, 4),
    ay = ROUND(ay, 4),
    az = ROUND(az, 4),
    timestamp= current_timestamp()
WHERE id>0;



