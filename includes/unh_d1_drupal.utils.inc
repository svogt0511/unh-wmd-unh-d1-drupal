<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 *
 * Utility functions.
 */

/**
 * Checks to see if google analytics module is enabled.
 */
function _unh_d1_drupal_google_analytics_is_enabled() {
  $ret = FALSE;
  
  // Check to make sure we have the google analytics module enabled and configured.
  $ga_id = variable_get('googleanalytics_account', '');
  $ga_id = (empty($ga_id) || ($ga_id == 'UA-') ? '' : $ga_id);
  $ga_enabled = module_exists('googleanalytics');
  if ($ga_enabled && !empty($ga_id)) {
    $ret = TRUE;
  }
  
  return $ret;
}


/**
 * Checks to see if the add to head module is enabled.
 */
function _d1_drupal_add_to_head_is_enabled() {
  $ret = FALSE;
  
  $ath_enabled = module_exists('add_to_head');
  $ath_profiles = variable_get('add_to_head_profiles', array());
  if ($ath_enabled && array_key_exists('google-track-enrollments', $ath_profiles)) {
    $ret = true;
  }
  
  return $ret;
}


/**
 * Sort course search results.  May be an array of any kind of course (d1 or non-d1).
 */
function _unh_d1_drupal_sort_courses_by_title($courses) {
  $ret = array();
  
  if (!empty($courses)) {
    uasort($courses, function ($a, $b) {
      // return strnatcasecmp($a['name'], $b['name']); }
      // Be careful here.  We are searching for D1 and non-D1 courses.  We will need to differentiate.
    
      if (!empty($node = unh_d1_drupal_get_course_node($a))) {
        $a_name = _unh_d1_drupal_non_d1_course_title($node);
      } else {
        $a_name = unh_d1_client_getcourseName($a);
      }
    
      if (!empty($node = unh_d1_drupal_get_course_node($b))) {
        $b_name = _unh_d1_drupal_non_d1_course_title($node);
      } else {
        $b_name = unh_d1_client_getcourseName($b);
      }
    
      return strnatcasecmp($a_name, $b_name); }
    );
    
    $ret = $courses;
  }
  
  return $ret;
}




