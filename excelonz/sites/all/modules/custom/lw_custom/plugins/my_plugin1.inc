<?php

/**
 * @file
 * Convert string to timestamp.
 */

$plugin = array(
  'form' => 'feeds_tamper_my_plugin1_form',
  'callback' => 'feeds_tamper_my_plugin1_callback',
  'name' => 'Where The Fields are changed tid1',
  'multi' => 'loop',
  'category' => 'Text',
);

function feeds_tamper_my_plugin1_form($importer, $element_key, $settings) {
  $form = array();
  $form['html'] = array(
    '#markup' => t('Where The Fields are changed tid 1.')
  );
  return $form;
}

function feeds_tamper_my_plugin1_callback($result, $item_key, $element_key, &$field, $settings) {

  $class = $field;

  $term_find_query = db_select('taxonomy_term_data', 'td')
    ->fields("td", array('tid'))
    ->condition("vid", 2)
    ->condition("name", $class)
    ->range(0, 1)
    ->execute()->fetchAll();
    $field = $term_find_query[0]->tid;
}
