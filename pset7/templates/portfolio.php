<div>
  <table class="table table-striped text-left">
    <thead>
      <tr>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
        <th>Total</th>
      </tr>
    </thead>
      <tbody>
      <?php foreach ($positions as $position): ?>
      <tr>
          <td><?= $position["symbol"] ?></td>
          <td><?= $position["shares"] ?></td>
          <td>$<?= number_format($position["price"], 2, '.', ','); ?></td>
          <td>$<?= number_format(intval($position["shares"]) * intval($position["price"]), 2, '.', ','); ?></td>
      </tr>
      <?php endforeach ?>
      <tr>
        <td>CASH</td>
        <td></td>
        <td></td>
        <td>$<?= number_format($cash, 2, '.', ','); ?></td>
      </tr>
    </tbody>
  </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
