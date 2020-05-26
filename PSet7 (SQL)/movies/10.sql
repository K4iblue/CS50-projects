SELECT name from people
JOIN directors ON directors.person_id = people.id
JOIN ratings ON ratings.movie_id = directors.movie_id
WHERE rating >= "9.0"