<?php

/**
 * Implements hook_settings().
 * Configuration settings page.
 *
 * @return
 *    Array of the system settings form.
 */
function noty_messages_settings() {
  $module_path = drupal_get_path('module', 'noty_messages');
  if (!libraries_get_path('noty')){
    $form['noty_messages_code_status'] = array(
      '#type' => 'fieldset',
      '#title' => t('noty Messages settings'),
      '#weight' => -10,
      '#description' => t('Please install noty'),
    );
    return $form;
  }
  $form['noty_messages_code_status'] = array(
  '#type' => 'fieldset',
  '#title' => t('noty Messages settings'),
  '#weight' => -10,
  );
  $form['noty_messages_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Noty Messages Plugin Settings',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['noty_messages_settings']['noty_messages_position'] = array(
    '#type' => 'select',
    '#title' => t('Position'),
    '#options' => array(
      0 => t('Top'),
      1 => t('Top Center'),
      2 => t('Bottom'),
      3 => t('Center'),
      4 => t('Top Left'),
      5 => t('Top Right'),
    ),
    '#description' => t('Where the messages should appear'),
  );
  return $form;
}
