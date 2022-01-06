# Arduino Moisture Sensing for the Private Cloud
An Arduino moisture sensing setup with Private Cloud connectivity.

## How to start in Docker
Build Docker image:
```
docker build -t urban-farming .
```

Start Docker container:
```
docker run -p 8000:8000 -d --restart unless-stopped urban-farming
```
