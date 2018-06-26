<?php
  $output = '';
  $form_state = $variables['form_state'];
  $filtered = $variables['filtered'];

  if (empty($form_state["storage"]["results"])) {
    $str = unh_d1_drupal_get_search_no_results_text() . unh_d1_drupal_get_search_again_button() . PHP_EOL;
  } else {

    $filters = NULL;
    if ($filtered) {
      $filter_titles = unh_d1_drupal_get_filter_title_list($form_state['storage']['filters']);
    }

    $str = '
<div name="search-results" class="search-results">';

    foreach ($form_state["storage"]["results"]["area"] as $area) {
      $str .= '
  <div class="search-area">
    <div class="search-area-header h2">' . $area['area_title'] . (($filtered && $filter_titles) ? ' (' . implode(',', $filter_titles) . ')' : '') . '</div>';

      foreach ($area['topic'] as $topic) {
        $str .= '
    <div class="search-topic">
      <div class="search-topic-header h3">' . $topic['topic_title'] . '</div>
      <div class="search-topic-body">';

        $str .= unh_d1_drupal_get_courseListBlock_markup($topic['courseProfiles']);

        $str .= '
      </div>
    </div>';
      }

      $str .= '
  </div>';
    }
    
    $str .= '
</div>';

    $str = unh_d1_drupal_get_search_again_button('top-of-page') . $str .  unh_d1_drupal_get_backToTop_button('search-results');
  }

  $output = $str;
?>

<?=$output?>
