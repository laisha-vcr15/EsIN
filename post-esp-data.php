<?php

/**
 * @author Laisha VC
 * Fecha: Antes de lo que piensa
 */

//Constructor
ini_set("memory_limit", "256M");

//Action
try {
    main(); //inicio
} catch (Throwable $th) {
    //throw $th;
    echo "Error: " . $th;
}


//funcion inicial
function main()
{
    try {
        $s1 = $_POST["s1"];
        $s2 = $_POST["s2"];
        $s3 = $_POST["s3"];
        $s4 = $_POST["s4"];

        eSQL("INSERT INTO `lectura_sensor` (`disponibilidad`,`id_sensor`) VALUES ( :disponibilidad, '1'); ", ["disponibilidad" => $s1]);
        eSQL("INSERT INTO `lectura_sensor` (`disponibilidad`,`id_sensor`) VALUES ( :disponibilidad, '2'); ", ["disponibilidad" => $s2]);
        eSQL("INSERT INTO `lectura_sensor` (`disponibilidad`,`id_sensor`) VALUES ( :disponibilidad, '3'); ", ["disponibilidad" => $s3]);
        eSQL("INSERT INTO `lectura_sensor` (`disponibilidad`,`id_sensor`) VALUES ( :disponibilidad, '4'); ", ["disponibilidad" => $s4]);

        $request = [];
        $request["chat_id"] = "@EsInTecMM";
        $request["text"] = "Disponibilidad de estacionamiento \xF0\x9F\x9A\x97 \n";
        $request["text"] .= "\nLugar 1: " . ($s1 ? "\xE2\x9D\x8C No Disponible" : "\xE2\x9C\x85 Disponible");
        $request["text"] .= "\nLugar 2: " . ($s2 ? "\xE2\x9D\x8C No Disponible" : "\xE2\x9C\x85 Disponible");
        $request["text"] .= "\nLugar 3: " . ($s3 ? "\xE2\x9D\x8C No Disponible" : "\xE2\x9C\x85 Disponible");
        $request["text"] .= "\nLugar 4: " . ($s4 ? "\xE2\x9D\x8C No Disponible" : "\xE2\x9C\x85 Disponible");



        $response["telegram"] =
            cCurl(
                "https://api.telegram.org/bot5345250302:AAFLTM9S6oy2bRd02_ioR1-YdYp_hUCD7FA/sendMessage",
                $request
            );
        echo json_encode($response);
    } catch (\Throwable $th) {
        echo ("Valio kk");
    }
}

function cCurl($url, $data = [])
{
    //API URL

    //create a new cURL resource
    $ch = curl_init($url);

    //attach encoded JSON string to the POST fields
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data);

    //return response instead of outputting
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    //execute the POST request
    $result = curl_exec($ch);

    //close cURL resource
    curl_close($ch);
    return $result;
}



// Funcion para crear conexion a db
function dbConnection($servername, $username, $password, $dbname, $port = 3306)
{
    // Variables para configuracion de conexion a db

    try {
        $pdo = new PDO("mysql:host=$servername;port=" . $port . ";dbname=$dbname;charset=utf8", $username, $password);
        return $pdo;
    } catch (PDOException $e) {
        echo "Hola: " . $e['getMessage']();
    }
}


function eSQL($sql, $data = [])
{
    // echo json_encode($data);
    $dbh = dbConnection("localhost", "root", "", "db_esin", 3306);
    // echo "Intentando ejecutar: " . $sql . ", <br>";
    $sth = $dbh->prepare($sql);
    $sth->execute($data);
    $result = $sth->fetchAll();
    if ($result) {
        // output data
        return $result;
    } else {
        return false;
    }
}
