<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php

echo "<pre>";print_r($output);die();
  global $user;

  $output = $row->field_field_time[0]['raw']['value'];

  $values = split(" ", $output);
  $dates = split("-", $values[0]);
  $times = split(":", $values[1]);

  $golive_time = mktime($times[0], $times[1], $times[2], $dates[1], $dates[2], $dates[0]);
  $now_time = time();

  $nid = $row->field_user_status_field_collection_item_nid;
//    print_r($nid);die();



 // if ($now_time > $golive_time) {
    /*
     * if author
     *  show start button
     * else other
     *  if check nid  if field is started
     *    show join button
     *  else
     *    show message "waiting for author to start"
     */
    if ($row->users_node_uid == $user->uid) {
      echo "start"; // Show start button.
      echo "<a href='/golive/take/".$nid."' id='show-on-time".$nid."'> start</a>";
    }
    else {
      $query = db_select('field_data_field_status', 'fs');
      $query
        ->condition('fs.entity_id', $nid, '=')
        ->fields('fs', array('field_status_value'));
      $result = $query->execute();

      //@todo add condition for finished.

      foreach ($result as $record){
      if ($record->field_status_value == 'started'){
         echo 'JOIN';
         echo "<a href='golive/take/".$nid."' id='show-on-start".$nid."'> join</a>";
       }
       else{
         echo "Waiting for author to start";
         echo "<a href='#' id='show-on-time".$nid."'> Waiting for author to start</a>";
       }
      }
    }
  //}
  //else{
    $rem_tim = $golive_time - $now_time;
    $rem_tim_ms = $rem_tim *1000;
     echo "<div class='rem_time'>" . $rem_tim . "</div>";

    echo $output . " rem time " .round($rem_tim/60);
  //}

    if($rem_tim > 0) {
      $inline_js = "<script>

        jQuery('#show-on-time".$nid."').hide();
     setTimeout(function(){
	  jQuery('#show-on-time".$nid."').show();
	  },".$rem_tim_ms.");
      </script>";
    }
    echo $inline_js
?>
