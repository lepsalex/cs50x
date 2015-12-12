<?php

    // configuration
    require("../includes/config.php");

    // Lookup user's holdings
    $rows = query("SELECT * FROM holdings WHERE id = ?", $_SESSION["id"]);

    // Build $rows
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }

    // Lookup user's cash balance
    $balances = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $balances[0]["cash"];

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "cash" => $cash]);

?>
