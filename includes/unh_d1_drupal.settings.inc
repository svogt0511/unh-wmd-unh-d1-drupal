<?php

/**
 * @file
 *
 * @todo: Update this docblock.
 * @todo: make sure we get full output on other than 'short' informationLevel
 *
 * Functions/'methods' get data from D1 using the web services.
 * For ex, get lists of things like: course lists, section lists, etc.
 *
 * Also functions/'methods' for getting information from the data structures
 * returned from D1, like determining course status, section status, etc.
 */

/******************************************************************************
 *
 * Calls to extract settings for this module.
 *
 ******************************************************************************/

/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_program_area() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_program_area', '');
  
  return $ret;
}


/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_google_track_enrollments() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_google_track_enrollments', '');
  
  return $ret;
}


//UTIL: Returns the google tracking call for enrollments (if we are tracking);
function unh_d1_drupal_get_enrollment_tracking_code($section) {
  $ret = '';
  
  if (!empty($section)) {
    $ret = (unh_d1_drupal_settings_google_track_enrollments() ? 'onclick="trackOutboundLink(\'' . unh_d1_client_get_enrollment_url($section) . '\'); return false;"' : '');
  }
  
  return $ret;
}



/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_blockTitle() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_blockTitle', '');
  
  return $ret;
}


/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_label() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_label', '');
  
  return $ret;
}


/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_tab() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_tab', '');
  
  return $ret;
}


/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_phrase() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_phrase', '');
  
  return $ret;
}


/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_submit() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_submit', '');
  
  return $ret;
}




/**
 * Returns the given module setting.
 */
function unh_d1_drupal_settings_courseSearchBar_filters() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_courseSearchBar_filters', '');
  
  return $ret;
}





