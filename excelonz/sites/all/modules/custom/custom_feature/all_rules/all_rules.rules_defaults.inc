<?php
/**
 * @file
 * all_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function all_rules_default_rules_configuration() {
  $items = array();
  $items['rules_new_mssage_when_parent_create_student'] = entity_import('rules_config', '{ "rules_new_mssage_when_parent_create_student" : {
      "LABEL" : "New Mssage When Parent Create Student",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_insert" ],
      "IF" : [
        { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } }
      ],
      "DO" : [
        { "drupal_message" : { "message" : "Kindly select your subscription " } }
      ]
    }
  }');
  $items['rules_parent_redirect'] = entity_import('rules_config', '{ "rules_parent_redirect" : {
      "LABEL" : "parent redirect",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "9",
      "TAGS" : [ "parent" ],
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "user_login" ],
      "IF" : [
        { "user_has_role" : {
            "account" : [ "account" ],
            "roles" : { "value" : { "5" : "5" } },
            "operation" : "OR"
          }
        },
        { "AND" : [] },
        { "NOT user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } },
        { "AND" : [] },
        { "NOT user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } }
      ],
      "DO" : [
        { "redirect" : { "url" : "\\u003C?php\\r\\nglobal $user, $base_url;\\r\\n  $uid = $user-\\u003Euid;\\r\\n\\r\\n    $query = db_select(\\u0027field_data_field_subjects\\u0027, \\u0027fs\\u0027);\\r\\n    $query-\\u003Ejoin(\\u0022field_data_field_child_id\\u0022, \\u0022ch\\u0022, \\u0022ch.entity_id = \\u0022. $uid);\\r\\n    $query-\\u003Ejoin(\\u0022profile\\u0022, \\u0022p\\u0022, \\u0022fs.entity_id=p.pid and p.uid = field_child_id_uid\\u0022);\\r\\n    $query-\\u003Efields(\\u0022fs\\u0022, array(\\u0027field_subjects_tid\\u0027))\\r\\n      -\\u003Econdition(\\u0027fs.bundle\\u0027, \\u0022student\\u0022);\\r\\n    $result = $query-\\u003Erange(0,1)-\\u003Eexecute()\\r\\n      -\\u003EfetchAll();\\r\\n\\r\\n      if(array_key_exists(0, $result)) {\\r\\n       echo $base_url . \\u0022\\/user\\/\\u0022.$uid;\\r\\n      }\\r\\n      else {\\r\\n        echo $base_url . \\u0022\\/admin\\/people\\/p2rp-create\\/student\\u0022;\\r\\n      }\\r\\n\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_payment_subject_allocation'] = entity_import('rules_config', '{ "rules_payment_subject_allocation" : {
      "LABEL" : "Payment subject allocation",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "commerce subscription" ],
      "REQUIRES" : [ "rules", "php", "entity" ],
      "ON" : [ "commerce_payment_transaction_insert" ],
      "DO" : [
        { "php_eval" : { "code" : "$status = [commerce-payment-transaction:status];\\r\\nif ($status == \\u0022Success\\u0022) {\\r\\n  function recursive_array_search1($needle,$haystack) {\\r\\n    foreach($haystack as $key=\\u003E$value) {\\r\\n        $current_key=$key;\\r\\n        if($needle==$value OR (is_array($value) \\u0026\\u0026 recursive_array_search1($needle,$value) !== false)) {\\r\\n            return true;\\r\\n        }\\r\\n    }\\r\\n    return false;\\r\\n  }\\r\\n  $order_id = [commerce-payment-transaction:order-id];\\r\\n  $fetch_order = db_select(\\u0027eck_subscription\\u0027, \\u0027s\\u0027)\\r\\n    -\\u003Efields(\\u0027s\\u0027)\\r\\n    -\\u003Econdition(\\u0027worksheet_tid\\u0027,\\u00270\\u0027)\\r\\n    -\\u003Econdition(\\u0027order_id\\u0027, $order_id)\\r\\n    -\\u003Eexecute()-\\u003EfetchAll();\\r\\n\\r\\n    $child_info = array();\\r\\n    foreach($fetch_order as $result) {\\r\\n      $c_uid =$result-\\u003Echild_uid;\\r\\n      $child_info[$c_uid][$result-\\u003Esubject_tid] = $result-\\u003Eqty;\\r\\n      $coupon_info[$c_uid][$result-\\u003Esubject_tid] = $result-\\u003Eoffercodeid;\\r\\n    }\\r\\n\\r\\n\\r\\n    global $user;\\r\\n    foreach($child_info as $child_uid =\\u003E $child_row) {\\r\\n      $prof_load = profile2_load_by_user($child_uid);\\r\\n\\r\\n\\r\\n      $uid = $user-\\u003Euid;\\r\\n      $today = date(\\u0022y.m.d\\u0022);\\r\\n      $time_final = strtotime($today);\\r\\n\\r\\n\\r\\n      foreach ($child_row as $subject1 =\\u003E $value) {\\r\\n        $query = db_select(\\u0027eck_expiry\\u0027, \\u0027exp\\u0027)\\r\\n                    -\\u003Efields(\\u0027exp\\u0027, array(\\u0027expiry_date\\u0027))\\r\\n                    -\\u003Econdition(\\u0027subject_tid\\u0027, $subject1)\\r\\n                    -\\u003Econdition(\\u0027child_id\\u0027, $child_uid)\\r\\n                    -\\u003Eexecute()\\r\\n                    -\\u003EfetchAll();\\r\\n        foreach($query as $key =\\u003E $value1){\\r\\n          db_update(\\u0027eck_expiry\\u0027)\\r\\n            -\\u003Efields(array(\\u0027status\\u0027 =\\u003E \\u00270\\u0027, \\u0027purchase_type\\u0027 =\\u003E \\u0027exp\\u0027))\\r\\n            -\\u003Econdition(\\u0027expiry_date\\u0027, $value1-\\u003Eexpiry_date)\\r\\n            -\\u003Econdition(\\u0027subject_tid\\u0027, $subject1)\\r\\n            -\\u003Econdition(\\u0027child_id\\u0027, $child_uid)\\r\\n            -\\u003Eexecute();\\r\\n          }\\r\\n        \\/\\/  echo \\u0022\\u003Cpre\\u003E\\u0022;print_r($query);print_r( $query[$value]);die();\\r\\n        if(!recursive_array_search1($subject1, $prof_load[\\u0027student\\u0027]-\\u003Efield_subjects)) {\\r\\n          $prof_load[\\u0027student\\u0027]-\\u003Efield_subjects[\\u0027und\\u0027][][\\u0027tid\\u0027] = $subject1;\\r\\n        }\\r\\n\\r\\n        $time_final1 = 0;\\r\\n        $offerid = $coupon_info[$child_uid][$subject1];\\r\\n        if($offerid != 0) {\\r\\n          $offer_query = db_select(\\u0027eck_offer_code\\u0027, \\u0027eo\\u0027)\\r\\n            -\\u003Efields(\\u0027eo\\u0027)\\r\\n            -\\u003Econdition(\\u0027id\\u0027, $offerid)\\r\\n            -\\u003Eexecute()\\r\\n            -\\u003EfetchAssoc();\\r\\n            if($offer_query[\\u0027offer_code_type\\u0027] == \\u0027month\\u0027) {\\r\\n              $value = $value + $offer_query[\\u0027offer_code_value\\u0027];\\r\\n            }\\r\\n            elseif($offer_query[\\u0027offer_code_type\\u0027] == \\u0027fixdate\\u0027) {\\r\\n              $time_final1 = $offer_query[\\u0027offer_code_fix_date\\u0027];\\r\\n            }\\r\\n        }\\r\\n\\r\\n        $days = $value;\\r\\n\\r\\n        if($time_final1 == 0) {\\r\\n          $time_final1 = strtotime(\\u0027+\\u0027.$days.\\u0027 month\\u0027,$time_final);\\r\\n        }\\r\\n\\r\\n        $entity = entity_create(\\u0022expiry\\u0022,    \\/\\/adds the entity\\r\\n          array(\\r\\n            \\u0027uid\\u0027 =\\u003E $uid,\\r\\n            \\u0027type\\u0027 =\\u003E \\u0027user\\u0027,\\r\\n            \\u0027child_id\\u0027 =\\u003E $child_uid,\\r\\n            \\u0027expiry_date\\u0027 =\\u003E $time_final1,\\r\\n            \\u0027subject_tid\\u0027 =\\u003E $subject1,\\r\\n            \\u0027status\\u0027=\\u003E 1,\\r\\n            \\u0027purchase_type\\u0027 =\\u003E \\u0027paid\\u0027,\\r\\n          )\\r\\n        );\\r\\n        $en = entity_save(\\u0027expiry\\u0027, $entity);\\r\\n       }\\r\\n      profile2_save($prof_load[\\u0027student\\u0027]);\\r\\n    }\\r\\n\\r\\n\\r\\n}" } }
      ]
    }
  }');
  $items['rules_payment_worksheet_allocation'] = entity_import('rules_config', '{ "rules_payment_worksheet_allocation" : {
      "LABEL" : "Payment Worksheet Allocation",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "commerce subscription" ],
      "REQUIRES" : [ "rules", "php", "entity" ],
      "ON" : [ "commerce_payment_transaction_insert" ],
      "DO" : [
        { "php_eval" : { "code" : "$status = [commerce-payment-transaction:status];\\r\\nif ($status == \\u0022Success\\u0022) {\\r\\n  function recursive_array_search12($needle,$haystack) {\\r\\n    foreach($haystack as $key=\\u003E$value) {\\r\\n        $current_key=$key;\\r\\n        if($needle==$value OR (is_array($value) \\u0026\\u0026 recursive_array_search12($needle,$value) !== false)) {\\r\\n            return true;\\r\\n        }\\r\\n    }\\r\\n    return false;\\r\\n  }\\r\\n  $order_id = [commerce-payment-transaction:order-id];\\r\\n  $fetch_order = db_select(\\u0027eck_subscription\\u0027, \\u0027s\\u0027)\\r\\n    -\\u003Efields(\\u0027s\\u0027)\\r\\n    -\\u003Econdition(\\u0027worksheet_tid\\u0027,\\u00270\\u0027,\\u0027\\u003C\\u003E\\u0027)\\r\\n    -\\u003Econdition(\\u0027order_id\\u0027, $order_id)\\r\\n    -\\u003Eexecute()-\\u003EfetchAll();\\r\\n\\r\\n    $child_info = array();\\r\\n    foreach($fetch_order as $result) {\\r\\n      $c_uid =$result-\\u003Echild_uid;\\r\\n      $child_info[$c_uid][$result-\\u003Esubject_tid] = $result-\\u003Eqty;\\r\\n      $coupon_info[$c_uid][$result-\\u003Esubject_tid] = $result-\\u003Eoffercodeid;\\r\\n    }\\r\\n\\r\\n\\r\\n    global $user;\\r\\n    foreach($child_info as $child_uid =\\u003E $child_row) {\\r\\n      $prof_load = profile2_load_by_user($child_uid);\\r\\n\\r\\n\\r\\n      $uid = $user-\\u003Euid;\\r\\n      $today = date(\\u0022y.m.d\\u0022);\\r\\n      $time_final = strtotime($today);\\r\\n\\r\\n\\r\\n      foreach ($child_row as $subject1 =\\u003E $value) {\\r\\n      \\/\\/  echo \\u0022\\u003Cpre\\u003E\\u0022;print_r($query);print_r( $query[$value]);die();\\r\\n        $time_final1 = 0;\\r\\n        $offerid = $coupon_info[$child_uid][$subject1];\\r\\n        if($offerid != 0) {\\r\\n          $offer_query = db_select(\\u0027eck_offer_code\\u0027, \\u0027eo\\u0027)\\r\\n            -\\u003Efields(\\u0027eo\\u0027)\\r\\n            -\\u003Econdition(\\u0027id\\u0027, $offerid)\\r\\n            -\\u003Eexecute()\\r\\n            -\\u003EfetchAssoc();\\r\\n            if($offer_query[\\u0027offer_code_type\\u0027] == \\u0027month\\u0027) {\\r\\n              $value = $value + $offer_query[\\u0027offer_code_value\\u0027];\\r\\n            }\\r\\n            elseif($offer_query[\\u0027offer_code_type\\u0027] == \\u0027fixdate\\u0027) {\\r\\n              $time_final1 = $offer_query[\\u0027offer_code_fix_date\\u0027];\\r\\n            }\\r\\n        }\\r\\n\\r\\n        $days = $value;\\r\\n\\r\\n        if($time_final1 == 0) {\\r\\n          $time_final1 = strtotime(\\u0027+\\u0027.$days.\\u0027 month\\u0027,$time_final);\\r\\n        }\\r\\n\\r\\n        $entity = entity_create(\\u0022worksheet_expiry\\u0022,    \\/\\/adds the entity\\r\\n          array(\\r\\n            \\u0027uid\\u0027 =\\u003E $uid,\\r\\n            \\u0027type\\u0027 =\\u003E \\u0027user\\u0027,\\r\\n            \\u0027child_id\\u0027 =\\u003E $child_uid,\\r\\n            \\u0027expiry_date\\u0027 =\\u003E $time_final1,\\r\\n            \\u0027subject_tid\\u0027 =\\u003E $subject1,\\r\\n            \\u0027status\\u0027=\\u003E 1,\\r\\n            \\u0027purchase_type\\u0027 =\\u003E \\u0027paid\\u0027,\\r\\n          )\\r\\n        );\\r\\n        $en = entity_save(\\u0027worksheet_expiry\\u0027, $entity);\\r\\n       }\\r\\n    \\r\\n    }\\r\\n\\r\\n\\r\\n}" } }
      ]
    }
  }');
  return $items;
}
