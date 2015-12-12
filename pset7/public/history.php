<?php

    // configuration
    require("../includes/config.php");

    // Lookup user's holdings and extract symbols
    $rows = query("SELECT * FROM history WHERE id = ? ORDER BY datetime DESC", $_SESSION["id"]);

    $transactions = [];
    foreach ($rows as $row)
    {
      $transactions[] = [
          "transaction" => $row["transaction"],
          "datetime" => $row["datetime"],
          "symbol" => $row["symbol"],
          "shares" => $row["shares"],
          "price" => $row["price"]
      ];
    }

    render("history.php", ["title" => "History", "transactions" => $transactions]);

?>
