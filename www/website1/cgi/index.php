#!/usr/bin/php-cgi
<?php
// Obligatoire pour CGI : envoyer l'entête HTTP
header("Content-Type: text/html");

// Début de la page HTML
echo "<html><body>";

// Affiche la query_string
echo "<h2>$_SERVER[QUERY_STRING]</h2>";

// Parse et affiche chaque paramètre GET
if (!empty($_GET)) {
    echo "<h3>Paramètres GET :</h3><ul>";
    foreach ($_GET as $key => $value) {
        echo "<li><b>$key</b> = $value</li>";
    }
    echo "</ul>";
} else {
    echo "<p>Aucun paramètre GET trouvé.</p>";
}

// Affiche le chemin du script
echo "<p>Script exécuté : " . $_SERVER["SCRIPT_FILENAME"] . "</p>";

// Fin
echo "</body></html>";
?>
