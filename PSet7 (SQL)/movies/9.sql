SELECT DISTINCT name from people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE year = 2004
ORDER by people.birth