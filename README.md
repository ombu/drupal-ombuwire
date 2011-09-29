OMBUWIRE
========

Help OMBU wire up a Drupal site

Features
--------
- FPO blocks to help setup layouts quickly



Spec
----

- Its going to be a module
- It's going to use the static sidebar
- It's going to show page status (in progress/done)
- Add urls for each item in the sitemap and tasks for wireframes & design.
- PHP structure off of sitemap like:

    array(
        'about-us' => array(
            'title'     => 'About Us',
            'status'    => IN_PROGRESS,
            'wireframe' => '/wf/8.jpg',
            'design'    => '/design/8.jpg',
            'static'    => '/static/8.html',
        ),
    );

Ideally we could make changes to the above w/out rebuild (cache clear is fine)
