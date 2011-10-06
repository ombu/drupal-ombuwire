OMBUWIRE
========

Helps _wire_ up a Drupal site from wireframs, designs, and static pages.

## Features

- FPO blocks to help setup layouts quickly

## Wireframe/Design/Static page menu

Ombu Wire creates a menu to show the various assets/specs associated with a Drupal url.
To create menu items, implement the `hook_ombuwire_sitemap()` hook which returns an
multidimensional array in the following format:

    $sitemap = array(
      array('#markup' => '<h3>Our Site</h3>'),
      '<front>' => array(
        '#title' => "Home",
        '#status' => OMBUWIRE_NOT_STARTED,
        'wireframe' => '/path/to/file.jpg',
        'design' => '/path/to/file.jpg',
        'static' => '/path/to/file.html',
      ),
      'about' => array(
        '#title' => "About",
        '#status' => OMBUWIRE_NOT_STARTED,
        'wireframe' => array(
          '/path/to/file.jpg',
          '/path/to/file.jpg',
        ),
        'design' => $path .'/design/c4-state-homepage.jpg',
        '#children' => array(
          'about/our-team' => array(
            '#title' => "Our Team",
            '#status' => OMBUWIRE_NOT_STARTED,
            'wireframe' => '/path/to/file.jpg',
            'design' => '/path/to/file.jpg',
          ),
        ),
      ),
    );

    return $sitemap;

There are a few options for each element of the array.  If the array element's key is:

- **a string**: It is treated as the 'root' url for the element.  All of the item's
displays are based from this url (ex: if the key is 'about', the wireframe will be at
'about/wireframe').  `<front>` is used for the site's `/` path.  The available values for
the element array are:
  - `#title`: The title used in the menu. required
  - `#status`: One of the status codes used to display icons.  Supported values are:
    - `OMBUWIRE_NOT_STARTED`
    - `OMBUWIRE_IN_PROGRESS`
    - `OMBUWIRE_IMPLEMENTED`
  - `#children`: A nested array with the child elements, same options as the parent array.
  - `wireframe`: The path to an image or an array of image paths to show.
  - `design`: The path to an image or an array of image paths to show.
  - `static`: The path to a static design to show. Used as the `src` of an `<iframe>`.
- **not a string**: If element contains:
  - `#markup` key: the value is passed into the generated menu at this position.