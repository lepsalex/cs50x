<?php

    require(__DIR__ . "/../includes/config.php");

    // ensure proper usage
    if (empty($_GET["geo"]))
    {
        http_response_code(400);
        exit;
    }

    // Explode string into array using multi-parameters
    function multiexplode ($delimiters,$string) {
        $ready = str_replace($delimiters, $delimiters[0], $string);
        $launch = explode($delimiters[0], $ready);
        return  $launch;
    }
    $geo = multiexplode(array(",", ", ", " ", ".","|",":"), $_GET["geo"]);

    // Count number of parameters in $geo
    $g_count = count($geo);

    // numerically indexed array of places
    $places = [];

    // search database for places matching $_GET["geo"]
    // -- start by building query base
    $query = "SELECT * FROM places WHERE ";
    foreach ($geo as $index => $s) {

      // If is numeric we can assume postal code (zip)
      if (is_numeric($s))
      {
        // Add to the query
        $query .= "postal_code LIKE '{$s}%'";
      } else {
        // Add to the query
        $query .=
          "(place_name  LIKE '{$s}%' OR " .
          (strlen($s) <= 2 ? "admin_code1 LIKE '{$s}%' OR country_code LIKE '{$s}%' OR " : '') .
          "admin_name1 LIKE '{$s}%')";
      }

      // If not at end of geo add "AND "
      if ($index < ($g_count - 1)) {
        $query .= " AND ";
      }
    }

    $places = query($query);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
