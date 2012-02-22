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
  $form['noty_messages_settings']['noty_messages_text_alignment'] = array(
    '#type' => 'select',
    '#title' => t('Text Alignment'),
    '#options' => array(
      0 => t('Left'),
      1 => t('Right'),
      2 => t('Center'),
      3 => t('Justify'),
    ),
    '#description' => t('Text alignment'),
  );
  $form['noty_messages_settings']['noty_messages_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#field_suffix' => t('ms'),
    '#description' => t('The time in milliseconds for the notice to fade in.'),
    '#default_value' => 500,
  );
  $form['noty_messages_settings']['noty_messages_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#field_suffix' => t('ms'),
    '#description' => t('The time in milliseconds the notice will display for, before fading out.'),
    '#default_value' => 5000,
  );
  $form['noty_messages_settings']['noty_messages_closable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Closable'),
    '#description' => t('Check to pause when cursor is over the message.'),
    '#default_value' => TRUE,
  );
  $form['noty_messages_settings']['noty_messages_click_close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close on self click'),
    '#description' => t('Click to close'),
    '#default_value' => TRUE,
  );
  $form['noty_messages_settings']['noty_messages_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#options' => array(
      0 => t('Default'), //@todo pull themes
    ),
    '#description' => t('Text alignment'),
  );
  $form['noty_messages_settings']['noty_messages_modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Modal'),
    '#description' => t('Should the background fade out'),
    '#default_value' => TRUE,
  );
  $form['noty_messages_settings']['noty_messages_modal_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Modal CSS'),
    '#description' => t('CSS to apply to the modal layer'),
    '#default_value' => '',
  );

  /*
   @todo:
   Theme pull
   animate open
   animate close?
   easing?
   force? which ones?
   buttons
    type - button class
    text = text
    click - callback on click
   on show
   on close
   clear queue?
  */
  return $form;
}
