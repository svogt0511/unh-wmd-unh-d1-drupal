<?php

/**
 * @file
 *
 * Functions for Non-D1 courses.  Equivalent to D1 functions for D1 courses.
 * Perhaps this should be in a separate module.
 *
 */

/**
 * 
 */
function _unh_d1_drupal_non_d1_course_is_available($node) {
  $ret = FALSE;
  
  $wrapper = entity_metadata_wrapper('node', $node);
  $availability = $wrapper->field_course_availability->value();
  $ret = ((strcasecmp($availability, UNH_D1_DRUPAL_NON_D1_COURSE_IS_AVAILABLE) == 0) ? TRUE : FALSE);

  return $ret;
}

/**
 * 
 */
function _unh_d1_drupal_non_d1_course_title($node) {
  $ret = '';
  
  $wrapper = entity_metadata_wrapper('node', $node);
  $ret = '';
  $ret = $wrapper->title->value();
  
  return $ret;
}

