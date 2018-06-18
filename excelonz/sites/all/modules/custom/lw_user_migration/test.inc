<?php

/**
 * @file
 * Migration classes for migrating users and profiles
 *
 * based on: drupal.org/node/1269066#comment-4988994
 * and:      drupal.org/node/1190958#comment-4616032
 */

/**
 * Abstract class as a base for all our migration classes
 */
abstract class lw_Basic_Migration extends Migration {
    public function __construct() {
        // Always call the parent constructor first for basic setup
        parent::__construct(MigrateGroup::getInstance('lwMigrate'));
        // Avoid known line ending issue: drupal.org/node/1705850
        ini_set('auto_detect_line_endings', TRUE);
    }
}

/**
 * User-only migration - not profile fields
 *
 * Data files are assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class lw_Step1_UserMigration extends lw_Basic_Migration {
    public function __construct() {
        parent::__construct();
        $student_csv = variable_get('migration_student_csv_file');
        $file_path =  'sites/default/files/student_csv/'.$student_csv;
        $this->description = t('Import an CSV-file (only "Account"-fields)');
        $columns = array(
            // "Source": ('Fieldname', 'Description')
            0 => array('MID', t('Member-ID (must be unique)')),
            1 => array('email', t('Email (Account)')),
            2 => array('name', t('Name (Account)')),
            3 => array('field_first_name', t('First Name (Account)')),
            4 => array('field_middle_name', t('Middle Name (Account)')),
            5 => array('field_last_name', t('Last Name (Account)')),
            6 => array('password', t('Password (Account)')),
            7 => array('field_date_of_birth', t('DOB (for Memberlist)')),
        );
        // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
        $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path, $columns, array('header_rows' => 1));
        $this->destination = new MigrateDestinationUser();
        $this->map = new MigrateSQLMap($this->machineName,
            array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
            )
            ),
            MigrateDestinationUser::getKeySchema()
        );

        // Mapped fields
        //Adding simple mapping for username(username are being generated from email id)
        //$this->addSimpleMappings(array('name'));
        $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
        $this->addFieldMapping('mail', 'email')
            ->defaultValue('')
            ->description(t('Email address'));
        $this->addFieldMapping('init')
            ->defaultValue('')
            ->description(t('Email address used for initial account creation'));
        $this->addFieldMapping('pass', 'password')
            ->defaultValue('asdf')
            ->description(t("User's password (plain text)"));
        $this->addFieldMapping('is_new')
            ->defaultValue(TRUE)
            ->description(t('Build the new user (0|1)'));
        $this->addFieldMapping('field_date_of_birth', 'field_date_of_birth')
            ->defaultValue('') // empty = unknown
            ->callbacks(array($this, 'fixTimestamp'))
            ->description(t('The birthday (for Memberlist)') . '.<br />' . t('Format') . ': "YYYY-MM-DD" <br />' . t('or') . ' "MM/DD/YYYY" <br />' . t('or') . ' "DD.MM.YYYY"');
        //first name
        $this->addFieldMapping('field_first_name', 'field_first_name')
            ->defaultValue('')
            ->description(t('First name'));
        //middlle name
        $this->addFieldMapping('field_middle_name', 'field_middle_name')
            ->defaultValue('')
            ->description(t('Middle name'));
        $this->addFieldMapping('field_last_name', 'field_last_name')
            ->defaultValue('')
            ->description(t('Last name'));
        $this->addFieldMapping('roles')
            ->defaultValue(6)
            ->description(DRUPAL_AUTHENTICATED_RID . t(' = "authenticated user"'));
        $this->addFieldMapping('theme')
            ->defaultValue('')
            ->description(t("User's default theme"));
        $this->addFieldMapping('signature')
            ->defaultValue('')
            ->description(t("User's signature"));
        $this->addFieldMapping('signature_format')
            ->defaultValue('filtered_html')
            ->description(t('Which filter applies to this signature'));
        $this->addFieldMapping('created')
            ->defaultValue(time())
            ->description(t('UNIX timestamp of user creation date'));
        $this->addFieldMapping('access')
            ->defaultValue(0)
            ->description(t('UNIX timestamp for previous time user accessed the site'));
        $this->addFieldMapping('login')
            ->defaultValue(0)
            ->description(t('UNIX timestamp for user\'s last login'));
        $this->addFieldMapping('status')
            ->defaultValue(1)
            ->description(t('Whether the user is active(1) or blocked(0)'));
        $this->addFieldMapping('timezone')
            ->defaultValue(t('Europe/London')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
            ->description(t("User's time zone"));
        $this->addFieldMapping('language')
            ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
            ->description(t("User's default language"));
        $this->addFieldMapping('picture')
            ->defaultValue(0)
            ->description(t('Avatar of the user'));

        // Other handlers
        if (module_exists('path')) {
            $this->addFieldMapping('path')
                ->defaultValue(NULL)
                ->description(t('Path alias'));
        }
        if (module_exists('pathauto')) {
            $this->addFieldMapping('pathauto')
                ->defaultValue(1)
                ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
        }
        // Unmapped destination fields
        $this->addUnmigratedDestinations(array('role_names', 'data'));
    }




    public function fixTimestamp($date) {
        // enable empty (= unknown) birthdayusername-string:
        if (strlen($date) > 0) {
            $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
        }
        return $date;
    }

   /*On migration username format for Student ID (firstname + first char of last name + last 2 digits of DOB)*/
    /*public function prepare(stdClass &$account, stdClass $row) {
         $f_name =  $account->field_first_name['und'][0]['value'];
         $l_name = drupal_substr($account->field_last_name['und'][0]['value'],0,1);;
         $dob =  $account->field_date_of_birth['und'][0]['value'];
             if(strpos($dob,'-') !== FALSE)
                $dob = substr($account->field_date_of_birth['und'][0]['value'],2,2);
         $account->name = $f_name .'.'. $l_name . $dob;
         return $account->name;
     }*/

}



/**
 * Profile2 field migration
 *
 * Data files are assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class lw_Step2_MemberlistMigration extends lw_Basic_Migration {
    public function __construct() {
        parent::__construct();
        global $user;
        $student_csv = variable_get('migration_student_csv_file');
        $file_path =  'sites/default/files/student_csv/'.$student_csv;
        $this->description = t('Import an CSV-file with Profile2-fields ("s"-fields)');
        $columns = array(
            // "Source": ('Fieldname', 'Description')
            0 => array('MID', t('Member-ID (must be unique)')),
            1 => array('email', t('Email (Account)')),
            2 => array('name', t('Name (Account)')),
            3 => array('field_first_name', t('First Name (Account)')),
            4 => array('field_middle_name', t('middle Name (Account)')),
            5 => array('field_last_name', t('Last Name (Account)')),
            6 => array('password', t('Password (Account)')),
            7 => array('field_date_of_birth', t('DOB (for Memberlist)')),
            8 => array('field_class_user', t('class name (for Memberlist)')),
            9 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
           10 => array('field_roll_numbers', t('roll number (for Memberlist)')),
           11 => array('field_sports', t('sports(for Memberlist)')),
           12 => array('field_music', t('music (for Memberlist)')),
           13 => array('field_arts_crafts', t('art and craft (for Memberlist)')),
           14 => array('field_student_school_identifier', t('School Identifier (for Memberlist)')),

        );
        // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
        $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path , $columns, array('header_rows' => 1));
        // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
        $this->dependencies = array('lw_Step1_User');
        $this->destination = new MigrateDestinationProfile2('student');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
        $this->map = new MigrateSQLMap($this->machineName,
            array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
            )
            ),
            MigrateDestinationProfile2::getKeySchema()
        );
        // Connecting the profile2 to the user:
        $this->addFieldMapping('uid', 'MID')
            ->sourceMigration('lw_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
            ->description(t('The assignment of profile2-items to the respective user'));

        // Mapped fields
        $this->addFieldMapping('field_mnr', 'MID')
            ->defaultValue(0)
            ->description(t('The Member-ID (must be unique)'));
        $this->addFieldMapping('field_mnr:language')
            ->defaultValue('und')
            ->description(t('The language of the Member-ID<br />("und" = no language)'));
        $this->addFieldMapping('field_username:language')
            ->defaultValue(t('en'))
            ->description(t('The language of the login name'));
        //first name
        $this->addFieldMapping('field_first_name', 'field_first_name')
            ->defaultValue('')
            ->description(t('First name'));
        $this->addFieldMapping('field_middle_name', 'field_middle_name')
            ->defaultValue('')
            ->description(t('Middle name'));
        $this->addFieldMapping('field_last_name', 'field_last_name')
            ->defaultValue('')
            ->description(t('Last name'));
        $this->addFieldMapping('field_name:language')
            ->defaultValue(t('en'))
            ->description(t('The language of the complete name'));
        //user class
        $this->addFieldMapping('field_class_user', 'field_class_user')
            ->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'class_split'))
            //  ->defaultValue(549)
            ->description(t('The class name for the user'));
        //field_subjects
        $this->addFieldMapping('field_subjects', 'field_subjects')
            ->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'subject_split'))
            ->defaultValue('')
            ->description(t('The subject name for the user'));
         //field_schools   
         $this->addFieldMapping('field_schools', 'field_student_school_identifier')
            //->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'student_school_name'))
            ->defaultValue('')
            ->description(t('The subject name for the user'));
        //field_roll_number
        $this->addFieldMapping('field_roll_numbers', 'field_roll_numbers')
            ->defaultValue('3')

            ->description(t('The roll number for the user'));
        
        $this->addFieldMapping('field_date_of_birth', 'field_date_of_birth')
            ->defaultValue('') // empty = unknown
            ->callbacks(array($this, 'fixTimestamp'))
            ->description(t('The birthday (for Memberlist)') . '.<br />' . t('Format') . ': "YYYY-MM-DD" <br />' . t('or') . ' "MM/DD/YYYY" <br />' . t('or') . ' "DD.MM.YYYY"');
        $this->addFieldMapping('field_school_city', 'field_student_school_identifier')
            //->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'student_school_city'))
            ->defaultValue('')
            ->description(t('The subject name for the user'));
          
         //field_school_branch   
        $this->addFieldMapping('field_branch', 'field_student_school_identifier')
            //->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'student_school_branch'))
            ->defaultValue('')
            ->description(t('The subject name for the user'));
       
        //field_sports
        $this->addFieldMapping('field_sports', 'field_sports')
            ->defaultValue('')
            ->description(t('The sports (for students)'));
        //field_music'
        $this->addFieldMapping('field_music', 'field_music')
            ->defaultValue('')
            ->description(t('The sports (for students)'));
        //field_arts_crafts'
        $this->addFieldMapping('field_arts_crafts', 'field_arts_crafts')
            ->defaultValue('')
            ->description(t('The art-craft (for students)'));

        //School Identifier
        $this->addFieldMapping('field_student_school_identifier', 'field_student_school_identifier')
            ->arguments(array('source_type' => 'tid'))
            ->callbacks(array($this, 'school_identifier'))
            ->defaultValue('')
            ->description(t('The subject name for the user'));

        // some internal fields
        $this->addFieldMapping('revision_uid')
            ->defaultValue($user->uid)
            ->description(t('The user ID of the user, who started the migration'));
        $this->addFieldMapping('language')
            ->defaultValue(t('en'))
            ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));

        // Unmapped fields (this fields are in core and not needed as profile2-fields)
        $this->addUnmigratedSources(array('mail', 'password'));
    }

    public function class_split($data) {
        // enable empty (= unknown) birthday-string:
        
        $ex_data = explode("-", $data);
        $class_name = $ex_data[0];
        $class_section = $ex_data[1];

        $term_find_query = db_select('taxonomy_term_data', 'td')
            ->fields("td", array('tid'))
            ->condition("vid", 2)
            ->condition("name", $class_name)
            ->range(0, 1)
            ->execute()->fetchAll();
        $class_tid = $term_find_query[0]->tid;

        $term_find_query = db_select('taxonomy_term_data', 'td');
        $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $class_tid);
        $term_find_query->fields('td', array("tid"))
            ->condition("vid", 2)
            ->condition("name", $class_section);
        $term_find_query_res = $term_find_query->execute()->fetchAll();
        $class_sec = $term_find_query_res[0]->tid;

        $data =  array($class_tid,$class_sec);

        return $data;
    }
    public function subject_split($data) {
	$opt = array();        
	// enable empty (= unknown) birthday-string:
         //Adding foreach for multiple subjects and topics field in student profile e.g Class 1 English
               $comma_split = explode(',',$data);
           foreach($comma_split as $key=>$value) {
              $ex_data = explode("-", $value);         
              $class_name = $ex_data[0];
              $class_subject = $ex_data[1];
              $query = db_select('taxonomy_term_data', 'fs');
              $query->fields('fs',array('tid',));
              $query->condition('name', $class_name);
              $query->range(0, 1);
        $result = $query->execute()->fetchAssoc();
        $subject_tid = $result['tid'];
        $term_find_query = db_select('taxonomy_term_data', 'td');
        $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $subject_tid);
        $term_find_query->fields('td', array("tid"))
            ->condition("vid", 7)
            ->condition("name", $class_subject);
        $term_find_query_res = $term_find_query->execute()->fetchAll();
        $class_subject_tid = $term_find_query_res[0]->tid;
        $opt[] = $class_subject_tid;
}
           return $opt;
}
    public function fixTimestamp($date) {
        // enable empty (= unknown) birthday-string:
        if (strlen($date) > 0) {
            $date = substr($date, 0, 10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
        }
        return $date;
    }
    
      public function school_identifier($data) {
              $query = db_select('node', 'n');
              $query->fields('n',array('Nid',));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
        $result = $query->execute()->fetchAssoc();
	     $nid = $result['Nid'];
	return $nid;
}
 
       public function student_school_name($data) {
		      $query = db_select('node', 'n');
              $query->INNERJOIN("field_data_field_school_name", "fsname", "fsname.entity_id = n.nid");
              $query->INNERJOIN("taxonomy_term_data", "ttd", "ttd.tid = fsname.field_school_name_tid");
              $query->fields("ttd", array("name"));
              $query->fields('n',array('Nid'));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
              $result = $query->execute()->fetchAssoc();
              $school_name = $result['name'];
	
	return $school_name;
}   

      public function student_school_city($data) {
	          $query = db_select('node', 'n');
              $query->INNERJOIN("field_data_field_partner_school_city", "fscity", "fscity.entity_id = n.nid");
              $query->INNERJOIN("taxonomy_term_data", "ttd", "ttd.tid = fscity.field_partner_school_city_tid");
              $query->fields("ttd", array("name"));
              $query->fields('n',array('Nid'));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
              $result = $query->execute()->fetchAssoc();
              $school_city = $result['name'];
    	return $school_city;
    }   
    public function student_school_branch($data) {
	          $query = db_select('node', 'n');
              $query->INNERJOIN("field_data_field_school_branch", "fsbranch", "fsbranch.entity_id = n.nid");
              $query->INNERJOIN("taxonomy_term_data", "ttd", "ttd.tid = fsbranch.field_school_branch_tid");
              $query->fields("ttd", array("name"));
              $query->fields('n',array('Nid'));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
              $result = $query->execute()->fetchAssoc();
              $school_branch = $result['name'];
    	return $school_branch;
    }
}

// $Id$


/**
 * @file
 * Manage Spandan Category term Migration
 */
/**
 * Migrate Parent Category terms
 *
 */
class lw_ParentTermMigration extends lw_Basic_Migration {
    public function __construct() {
        parent::__construct();
        $this->description = t('Category term migration');
        $student_csv = variable_get('migration_student_csv_file');
        $file_path =  'sites/default/files/student_csv/'.$student_csv;

        $columns = array(
            0 => array('MID', t('Member-ID (must be unique)')),
            1 => array('email', t('Email (Account)')),
            2 => array('name', t('Name (Account)')),
            3 => array('field_first_name', t('First Name (Account)')),
            4 => array('field_middle_name', t('middle Name (Account)')),
            5 => array('field_last_name', t('Last Name (Account)')),
            6 => array('password', t('Password (Account)')),
            7 => array('field_date_of_birth', t('DOB (for Memberlist)')),
            8 => array('field_class_user', t('class name (for Memberlist)')),
            9 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
            10 => array('field_schools', t('school name (for Memberlist)')),
            11 => array('field_roll_numbers', t('roll number (for Memberlist)')),
            //12 => array('field_section', t('section (for Memberlist)')),
            12 => array('field_city', t('city (for Memberlist)')),
            13 => array('field_branch', t('branch (for Memberlist)')),
            14 => array('field_sports', t('sports(for Memberlist)')),
            15 => array('field_music', t('music (for Memberlist)')),
            16 => array('field_arts_crafts', t('art and craft (for Memberlist)')),
            17 => array('field_student_school_identifier', t('School Identifier (for Memberlist)')),
        );

        // TIP: delete ", array('header_rows' => 1)" in the next line, when the CSV-file has NO header-line
        $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path , $columns, array('header_rows' => 1));
        // Create a map object for tracking the relationships between source rows
        // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
        // class, which uses database tables for tracking. Pass the machine name
        // (BeerTerm) of this migration to use in generating map and message tables.
        // And, pass schema definitions for the primary keys of the source and
        // destination - we need to be explicit for our source, but the destination
        // class knows its schema already.

        $this->map = new MigrateSQLMap($this->machineName,
            array(
                'field_schools' => array('type' => 'varchar',
                    'length' => 255,
                    'not null' => TRUE,
                    'description' => 'User\'s Member-ID',
                )
            ),
            MigrateDestinationTerm::getKeySchema()
        );

        // Set up our destination - terms in the migrate_example_beer_styles vocabulary
        $this->destination = new MigrateDestinationTerm('school');

        // Assign mappings TO destination fields FROM source fields. To discover
        // the names used in these calls, use the drush commands
        // drush migrate-fields-destination BeerTerm
        // drush migrate-fields-source BeerTerm
        $this->addFieldMapping('name', 'field_schools');
        $this->addFieldMapping('description', 'CLASS_CODE')->defaultValue('');
        $this->addFieldMapping('weight')
            ->defaultValue('0');

        // un-mapped field
        $this->addFieldMapping('format')
            ->issueGroup(t('DNM'));
        $this->addFieldMapping('field_schools')
            ->issueGroup(t('DNM'));
        $this->addFieldMapping('language')
            ->defaultValue(t('en'));
    }
    public function prepare(stdClass $account, stdClass $row) {
        //print_r($row);
        //print_r($account);
    }
}

class lw_ParentBranchMigration extends lw_Basic_Migration {
    public function __construct() {
        parent::__construct();
        $this->description = t('Category term migration');
        $student_csv = variable_get('migration_student_csv_file');
        $file_path =  'sites/default/files/student_csv/'.$student_csv;

        $columns = array(
            0 => array('MID', t('Member-ID (must be unique)')),
            1 => array('email', t('Email (Account)')),
            2 => array('name', t('Name (Account)')),
            3 => array('field_first_name', t('First Name (Account)')),
            4 => array('field_middle_name', t('middle Name (Account)')),
            5 => array('field_last_name', t('Last Name (Account)')),
            6 => array('password', t('Password (Account)')),
            7 => array('field_date_of_birth', t('DOB (for Memberlist)')),
            8 => array('field_class_user', t('class name (for Memberlist)')),
            9 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
            10 => array('field_schools', t('school name (for Memberlist)')),
            11 => array('field_roll_numbers', t('roll number (for Memberlist)')),
            //12 => array('field_section', t('section (for Memberlist)')),
            12 => array('field_city', t('city (for Memberlist)')),
            13 => array('field_branch', t('branch (for Memberlist)')),
            14 => array('field_sports', t('sports(for Memberlist)')),
            15 => array('field_music', t('music (for Memberlist)')),
            16 => array('field_arts_crafts', t('art and craft (for Memberlist)')),
            17 => array('field_student_school_identifier', t('School Identifier (for Memberlist)')),
        );

        // TIP: delete ", array('header_rows' => 1)" in the next line, when the CSV-file has NO header-line
        $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path , $columns, array('header_rows' => 1));
        // Create a map object for tracking the relationships between source rows
        // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
        // class, which uses database tables for tracking. Pass the machine name
        // (BeerTerm) of this migration to use in generating map and message tables.
        // And, pass schema definitions for the primary keys of the source and
        // destination - we need to be explicit for our source, but the destination
        // class knows its schema already.

        $this->map = new MigrateSQLMap($this->machineName,
            array(
                'field_branch' => array('type' => 'varchar',
                    'length' => 255,
                    'not null' => TRUE,
                    'description' => 'User\'s Member-ID',
                )
            ),
            MigrateDestinationTerm::getKeySchema()
        );

        // Set up our destination - terms in the migrate_example_beer_styles vocabulary
        $this->destination = new MigrateDestinationTerm('branch');

        // Assign mappings TO destination fields FROM source fields. To discover
        // the names used in these calls, use the drush commands
        // drush migrate-fields-destination BeerTerm
        // drush migrate-fields-source BeerTerm
        $this->addFieldMapping('name', 'field_branch');
        $this->addFieldMapping('description', 'CLASS_CODE')->defaultValue('');
        $this->addFieldMapping('weight')
            ->defaultValue('0');

        // un-mapped field
        $this->addFieldMapping('format')
            ->issueGroup(t('DNM'));
        $this->addFieldMapping('field_branch')
            ->issueGroup(t('DNM'));
        $this->addFieldMapping('language')
            ->defaultValue(t('en'));
    }
    public function prepare(stdClass $account, stdClass $row) {
        //print_r($row);
        //print_r($account);
    }
}



