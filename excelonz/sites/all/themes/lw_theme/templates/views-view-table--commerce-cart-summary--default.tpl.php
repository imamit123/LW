
<table <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
  <?php
    $free_dis = TRUE;
  $count = 0; ?>
    <?php foreach ($rows as $row_count => $row): ?>
<?php 
$arr_line_item[] = $row['line_item_id'];
$tot_count = db_select('eck_subscription','e')
        ->fields('e', array('order_id'))
        ->condition('line_item_id', $arr_line_item, 'IN')
        ->condition('worksheet_tid', '0','=')
        ->execute();
    
      $no_of_res = $tot_count->rowCount();
      $count = $no_of_res;
$class_std = $row['php'];
$dt = $row['php_1'];

  if(trim($row['commerce_total']) == 'General Knowledge') {
    $free_dis = FALSE;
  }
?>
<tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
        <?php foreach ($row as $field => $content): ?>
          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
<?php

if($count>1 && $free_dis): ?>
<?php
$cls = "odd";
if($count%2 == 0) {
$cls = "event";
}
?>
    <tr class=<?php echo $cls; ?>>
      <td class="views-field views-field-php">
		<?php echo $class_std;?>
      </td>
      <td class="views-field views-field-commerce-total views-align-right price">
	General Knowledge
      </td>
      <td class="views-field views-field-nothing">
	Complimentary
      </td>
      <td class="views-field views-field-php-1">
      <?php echo $dt;?>
      </td>
    </tr>
<?php endif; ?>

</tbody>
</table>
