<div>
  <table class="table table-striped text-left">
    <thead>
      <tr>
        <th>Transaction</th>
        <th>Date/Time</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
      </tr>
    </thead>
      <tbody>
      <?php foreach ($transactions as $row): ?>
      <tr>
          <td><?= $row["transaction"] ?></td>
          <?php $date = date_create($row["datetime"], timezone_open('UTC')); ?>
          <td><?= date_format($date, 'Y-m-d, g:ia') ?></td>
          <td><?= $row["symbol"] ?></td>
          <td><?= $row["shares"] ?></td>
          <td>$<?= number_format($row["price"], 2, '.', ','); ?></td>
      </tr>
      <?php endforeach ?>
    </tbody>
  </table>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
