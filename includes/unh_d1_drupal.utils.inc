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

