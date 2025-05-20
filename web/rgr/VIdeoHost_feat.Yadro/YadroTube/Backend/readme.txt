Пример запросов через curl

Регистрация (вам нужно реализовать свою регистрацию, так как стандартная JWT не включает эту функциональность):

bash
curl -X POST http://localhost:8000/api/auth/register/ -H "Content-Type: application/json" -d '{"username": "user", "password": "pass"}'

Авторизация:

bash
curl -X POST http://localhost:8000/api/token/ -H "Content-Type: application/json" -d '{"username": "user", "password": "pass"}'

Загрузка видео (с токеном):

bash
curl -X POST http://localhost:8000/api/videos/ -H "Authorization: Bearer YOUR_TOKEN" -F "title=My Video" -F "file=@/path/to/video.mp4"