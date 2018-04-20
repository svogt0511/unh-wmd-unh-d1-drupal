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
 * Returns the program area as set in this module's settings.
 */
function unh_d1_drupal_settings_program_area() {
  $ret = NULL;
  
  $ret = variable_get('unh_d1_drupal_program_area', '');
  
  return $ret;
}