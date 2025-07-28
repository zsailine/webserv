<?php
header("Content-type: text/html; charset=UTF-8");
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
        print_r($_POST); // Affiche les données POST
        echo "</pre>";
    ?>
    <div id="main">
        <h1>Hello webserv !</h1>
        <form method="POST" action="/index.php" >
            <label for="name"> Nom</label>
            <input type="text" name="name"/>
            <button type="submit">Submit</button>
        </form>
    </div>
</body>
</html>