<?php
/**
 * @file
 * all_entity_types.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function all_entity_types_eck_bundle_info() {
  $items = array(
  'parent_assignment_parent_assignment' => array(
  'machine_name' => 'parent_assignment_parent_assignment',
  'entity_type' => 'parent_assignment',
  'name' => 'parent_assignment',
  'label' => 'parent_assignment',
),
  'worksheet_expiry_worksheet_expiry' => array(
  'machine_name' => 'worksheet_expiry_worksheet_expiry',
  'entity_type' => 'worksheet_expiry',
  'name' => 'worksheet_expiry',
  'label' => 'worksheet_expiry',
),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function all_entity_types_eck_entity_type_info() {
$items = array(
       'expiry' => array(
  'name' => 'expiry',
  'label' => 'expiry',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'subject_tid' => array(
      'label' => 'child_id',
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
       'offer_code' => array(
  'name' => 'offer_code',
  'label' => 'Offer Code',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
    'offer_code' => array(
      'label' => 'offer_code',
      'type' => 'text',
      'behavior' => '',
    ),
    'offer_code_apply_to' => array(
      'label' => 'offer_code_apply_to',
      'type' => 'text',
      'behavior' => '',
    ),
    'offer_code_type' => array(
      'label' => 'offer_code_type',
      'type' => 'text',
      'behavior' => '',
    ),
    'offer_code_value' => array(
      'label' => 'offer_code_value',
      'type' => 'integer',
      'behavior' => '',
    ),
    'offer_code_from_date' => array(
      'label' => 'offer_code_from_date',
      'type' => 'text',
      'behavior' => '',
    ),
    'offer_code_end_date' => array(
      'label' => 'offer_code_end_date',
      'type' => 'text',
      'behavior' => '',
    ),
    'status' => array(
      'label' => 'status',
      'type' => 'integer',
      'behavior' => '',
    ),
    'offer_code_fix_date' => array(
      'label' => 'offer_code_fix_date',
      'type' => 'text',
      'behavior' => '',
    ),
    'agent_id' => array(
      'label' => 'agent_id',
      'type' => 'integer',
      'behavior' => '',
    ),
    'sold' => array(
      'label' => 'Sold',
      'type' => 'integer',
      'behavior' => '',
    ),
    'use_one_time' => array(
      'label' => 'Use One Time',
      'type' => 'integer',
      'behavior' => '',
    ),
    'offer_code_class' => array(
      'label' => 'offer_code_class',
      'type' => 'integer',
      'behavior' => '',
    ),
    'offer_code_subject' => array(
      'label' => 'offer_code_subject',
      'type' => 'text',
      'behavior' => '',
    ),
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
  ),
),
       'subscription' => array(
  'name' => 'subscription',
  'label' => 'subscription',
  'properties' => array(
    'uid' => array(
      'label' => 'Author',
      'type' => 'integer',
      'behavior' => 'author',
    ),
    'child_uid' => array(
      'label' => 'child_uid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'line_item_id' => array(
      'label' => 'line_item_id',
      'type' => 'integer',
      'behavior' => '',
    ),
    'order_id' => array(
      'label' => 'order_id',
      'type' => 'integer',
      'behavior' => '',
    ),
    'qty' => array(
      'label' => 'qty',
      'type' => 'integer',
      'behavior' => '',
    ),
    'subject_tid' => array(
      'label' => 'subject_tid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'created' => array(
      'label' => 'Created',
      'type' => 'integer',
      'behavior' => 'created',
    ),
    'offercodeid' => array(
      'label' => 'offercodeid',
      'type' => 'integer',
      'behavior' => '',
    ),
    'worksheet_tid' => array(
      'label' => 'worksheet_tid',
      'type' => 'integer',
      'behavior' => '',
    ),
  ),
),
  );
  return $items;
}
