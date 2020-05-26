SELECT title from movies

JOIN ratings ON ratings.movie_id = stars.movie_id
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id

WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5