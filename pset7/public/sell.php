<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
      // Lookup user's holdings and extract symbols
      $rows = query("SELECT symbol FROM holdings WHERE id = ?", $_SESSION["id"]);

      $positions = [];
      foreach ($rows as $row)
      {
        $positions[] = [
          "symbol" => $row["symbol"]
        ];
      }

      // Ensure the user has stocks to sell
      if (!empty($positions))
      {
        // Render Sell form
        render("sell_form.php", ["title" => "Sell", "positions" => $positions]);
      }
      else
      {
        apologize("Nothing to sell.");
      }
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
      // Get Price and Quantity to credit back to account
      $holding = query("SELECT shares FROM holdings WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
      $qty = $holding[0]["shares"];
      $price = lookup($_POST["symbol"]);
      $total = $qty * intval($price["price"]);

      // Sell Shares (remove from holdings for this user)
      $sell_shares = query("DELETE FROM holdings WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

      // If successfully deleted shares credit account
      if ($sell_shares !== FALSE)
      {
        // Credit the user with the proceeds of the sale
        $credit = query("UPDATE users SET cash = cash + $total WHERE id = ?", $_SESSION["id"]);

        // Store transaction to History
        $history = query("INSERT INTO history (id, transaction, symbol, shares, price) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "SELL", $_POST["symbol"], $qty, $price["price"]);

        // redirect to portfolio
        redirect("/");
      }
    }

?>
