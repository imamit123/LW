<?php
/**
 * @file
 * add_new_fields_in_feed_for_cck.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function add_new_fields_in_feed_for_cck_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
