<?php

function unh_d1_drupal_topicAreasWithChildren($terms_nested) {

  $terms = $terms_nested;
  if (!empty($terms)) {
    foreach($terms as $term) {
      if (!empty($term->children) && unh_d1_drupal_term_is_area($term)) {
      //if (!empty($term->children)) {
        return TRUE;
      }
    }
  }

  return FALSE;
}


function unh_d1_drupal_get_term_type($term) {
  return $term->field_type['und'][0]['value'];
}

function unh_d1_drupal_term_is_area($term) {
  return unh_d1_drupal_get_term_type($term) == 'area';
}

function unh_d1_drupal_term_is_topic($term) {
  return unh_d1_drupal_get_term_type($term) == 'topic';
}



//UTIL: GIVEN A TAXONOMY ID, RETURNS A NESTED REPRESENTATION
function unh_d1_drupal_get_nested_tree($vid) {
  $tree = taxonomy_get_tree($vid);
  $terms_flat = entity_load('taxonomy_term', FALSE, array('vid' => $vid));
  $list = array(); $nested=array();
  foreach ($tree as $term) {
    $term->children = array();
    $list[$term->tid] = $term;
  }
  uasort($list,function ($a, $b) {  return $a->weight > $b->weight; });
  foreach ($list as $tid=>&$term) {
    foreach ($term->parents as $ptid) {
      if (!empty($list[$ptid])) $list[$ptid]->children[$tid] = $term;
      else if ($ptid=='0') {
        $nested[$tid] = $term;
        $nested[$tid]->field_keyword = $terms_flat[$tid]->field_keyword;
        $nested[$tid]->field_type = $terms_flat[$tid]->field_type;
      }
    }
  }

  return $nested;
}


// very important!! changes relative urls to images in the course description to absolute urls to images that reside on d1 server
function unh_d1_drupal_filter ($value) {

  $pattern = '/src="\//s';

  $replacement = 'src="//' . unh_d1_client_settings_public_domain() . '/';

  $ret = preg_replace($pattern, $replacement, $value);

  return $ret;

}


// Get rid of multiple items that are the same in an array, based on the value of a given key.
// http://stackoverflow.com/questions/28596110/remove-duplicates-based-on-a-specific-key

function unh_d1_drupal_array_key_unique($arr, $key) {
    $uniquekeys = array();
    $output     = array();
    foreach ($arr as $item) {
        if (!in_array($item[$key], $uniquekeys)) {
            $uniquekeys[] = $item[$key];
            $output[]     = $item;
        }
    }
    return $output;
}

// used with usort to sort an array based on a given key value. (NOT USED ANY MORE!)
// ex: usort($courses_filtered, compare_courseTitle);
//  http://www.the-art-of-web.com/php/sortarray/

function unh_d1_drupal_compare_courseTitle($a, $b)
{
  return strnatcasecmp($a['name'], $b['name']);
}


// Search a multi-dim array for an element that is an array and the element
// contains an item with the given key and value.
// Returns NULL or the index of the item that has the value.
function unh_d1_drupal_array_search($key = '', $value = '', $arr = array()) {

    $ret = NULL;

    foreach ($arr as $key1 => $element) {
        if (is_array($element)) {
            if (array_key_exists($key, $element) && ($element[$key] === $value)) {
                $ret = $key1;
                break;
            }
        }
    }

    return $ret;
}

/**
 * Given a course of unknown type, determine its type and return its title.
 *
 */
function unh_d1_drupal_getCourseTitle($course = NULL) {
  $ret = NULL;

  if (unh_d1_client_course_is_d1($course)) {
    // get the name
  } elseif (unh_d1_drupal_course_is_non_d1($course)) {
    // get the name
  }

  return $ret;
}




