<?php
header("Content-type: text/html; charset=UTF-8");


$uploadDir = __DIR__ . "/uploads/";
if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0777, true);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // --- DELETE ---
    if (isset($_POST['delete_file'])) {
        $fileToDelete = basename($_POST['delete_file']);
        $targetPath = $uploadDir . $fileToDelete;
        if (file_exists($targetPath)) {
            unlink($targetPath);
            $message = "Fichier '$fileToDelete' supprimé.";
        } else {
            $message = "Fichier '$fileToDelete' introuvable.";
        }
    }
    else {
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
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.8/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-sRIl4kxILFvY47J16cr9ZwB07vP4J8+LH7qKQnuqkuIAvNWLzeN8tE5YBujZqJLB" crossorigin="anonymous">
    <title>Webserv</title>
</head>
<body style="background: white; padding: 50px;">
    <h1 style="color: black">Hello webserv !</h1>

    <?php if (!empty($message)) echo "<p><b>$message</b></p>"; ?>

    <form class="d-block" method="POST" action="index.php" enctype="multipart/form-data">
        <div>
            <label for="name">Nom</label>
            <input class="form-control" type="text" name="name"/>
        </div>
        <div>
            <label for="age">Age</label>
            <input class="form-control" type="text" name="age"/>
        </div>
        <div>
            <label for="avatar">Upload un fichier</label>
        </div>
        <div>
            <input class="form-control" type="file" name="avatar"/>
        </div>
        <div>
            <button class="mt-3 btn btn-success" type="submit">Submit</button>
        </div>
    </form>

    <hr>

    <h2>Fichiers uploadés</h2>
    <ul>
        <?php
        $files = array_diff(scandir($uploadDir), ['.', '..']);
        foreach ($files as $file) {
            if ($file === "data.txt") continue;
            echo "<li>$file 
                    <form method='POST' action='/index.php' style='display:inline'>
                        <input type='hidden' name='delete_file' value='$file'/>
                        <button class=\"mx-3 btn btn-danger\" type='submit'>Delete</button>
                    </form>
                  </li>";
        }
        ?>
    </ul>

</body>
</html>
