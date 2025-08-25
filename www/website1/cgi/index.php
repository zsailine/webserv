<?php
header("Content-type: text/html; charset=UTF-8");

// --- Dossier de stockage ---
$uploadDir = __DIR__ . "/uploads/";
if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0777, true);
}

// --- Sauvegarde des champs POST ---
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Stockage des données textuelles
    $logFile = $uploadDir . "data.txt";
    $fh = fopen($logFile, "a");
    if ($fh) {
        $time = date("Y-m-d H:i:s");
        fwrite($fh, "==== POST @ $time ====\n");
        foreach ($_POST as $key => $value) {
            fwrite($fh, "$key = $value\n");
        }
        fwrite($fh, "\n");
        fclose($fh);
    }

    // --- Gestion des fichiers uploadés ---
    if (!empty($_FILES)) {
        foreach ($_FILES as $fileField => $fileInfo) {
            if ($fileInfo['error'] === UPLOAD_ERR_OK) {
                $tmpName = $fileInfo['tmp_name'];
                $fileName = basename($fileInfo['name']);
                $targetPath = $uploadDir . $fileName;
                move_uploaded_file($tmpName, $targetPath);
            }
        }
    }
}

echo "Hello";
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./style.css"> 
    <title>Webserv</title>
</head>
<body>
    <?php
        echo "<pre>";
        print_r($_POST);  // debug POST
        print_r($_FILES); // debug fichiers uploadés
        echo "</pre>";

        if (!empty($_POST)) {
            echo 'Bonjour ' . htmlspecialchars($_POST["name"]) . 
                 ", tu as " . htmlspecialchars($_POST["age"]) . ' ans !';
        }
    ?>
    <div id="main">
        <h1>Hello webserv !</h1>
        <form method="POST" action="/index.php" enctype="multipart/form-data">
            <label for="name">Nom</label>
            <input type="text" name="name"/>

            <label for="age">Age</label>
            <input type="text" name="age"/>

            <label for="avatar">Upload un fichier</label>
            <input type="file" name="avatar"/>

            <button type="submit">Submit</button>
        </form>
    </div>
</body>
</html>
