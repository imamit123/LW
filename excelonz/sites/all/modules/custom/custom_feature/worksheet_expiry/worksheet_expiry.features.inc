<?php
/**
 * @file
 * worksheet_expiry.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function worksheet_expiry_eck_entity_type_info() {
$items = array(
       'worksheet_expiry' => array(
  'name' => 'worksheet_expiry',
  'label' => 'worksheet_expiry',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'subject_tid' => array(
      'label' => 'subject_tid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'child_id' => array(
      'label' => 'child_id',
      'type' => 'integer',
      'behavior' => '',
    ),
    'expiry_date' => array(
      'label' => 'expiry_date',
      'type' => 'integer',
      'behavior' => '',
    ),
    'status' => array(
      'label' => 'status',
      'type' => 'integer',
      'behavior' => '',
    ),
    'purchase_type' => array(
      'label' => 'purchase_type',
      'type' => 'text',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
