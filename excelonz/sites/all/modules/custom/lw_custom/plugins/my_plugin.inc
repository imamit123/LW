<?php

/**
 * @file
 * Convert string to timestamp.
 */

$plugin = array(
  'form' => 'feeds_tamper_my_plugin_form',
  'callback' => 'feeds_tamper_my_plugin_callback',
  'name' => 'Where The Fields are changed tid',
  'multi' => 'loop',
  'category' => 'Text',
);

function feeds_tamper_my_plugin_form($importer, $element_key, $settings) {
  $form = array();
  $form['html'] = array(
    '#markup' => t('Where The Fields are changed tid.')
  );
  return $form;
}

function feeds_tamper_my_plugin_callback($result, $item_key, $element_key, &$field, $settings) {

  $class = $result->items[$item_key]['class'];

  $term_find_query = db_select('taxonomy_term_data', 'td')
    ->fields("td", array('tid'))
    ->condition("vid", 2)
    ->condition("name", $class)
    ->range(0, 1)
    ->execute()->fetchAll();
    $class_tid = $term_find_query[0]->tid;
 //echo '--' . $class_tid . "++";

 // / print_r($class_tid);die();
  $query = db_select('field_data_field_subject', 'fs');
   $query->fields('fs',array('field_subject_tid',));
    $query->condition('bundle', 'class');
    $query->condition('entity_id', $class_tid);
    $query->range(0, 1);
    $result = $query->execute()->fetchAssoc();
  // print_r($result);die();
  $subject_tid = $result['field_subject_tid'];
  //echo '--' . $subject_tid . "++";

  $subject_child = taxonomy_get_tree(7, $subject_tid);

//echo "<pre>";print_r($subject_child);
//die();

  foreach ($subject_child as $key => $value) {
    if($value->name == $field) {
      //echo $value->
      $field = $value->tid;
    }
  }

}
